
#ifndef LCD_H_
#define LCD_H_
#include "I2C.h"

#define LCD_RS	0
#define LCD_RW	1
#define LCD_E	2
#define LCD_BACKLIGHT	3
#define LCD_DEV_ADDR	(0x27<<1)

#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_DISPLAY_ON		0x0c
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_ENTRY_MODE		0x06
#define COMMAND_4_BIT_MODE		0x28

uint8_t I2C_LCD_Data;

void LCD_DATA4bit(uint8_t data)
{
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | (data & 0xf0);
	LCD_EnablePin();
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | (data & 0x0f) << 4;
	LCD_EnablePin();
}

void LCD_EnablePin()
{
	I2C_LCD_Data &= ~(1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	
	I2C_LCD_Data |= (1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	
	I2C_LCD_Data &= ~(1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	
	_delay_us(1600);
}

void LCD_WriteCommand(uint8_t commadData)
{
	I2C_LCD_Data &= ~(1<<LCD_RS);
	I2C_LCD_Data &= ~(1<<LCD_RW);
	LCD_DATA4bit(commadData);
}

void LCD_WriteData(uint8_t charData)
{
	I2C_LCD_Data |= (1<<LCD_RS);
	I2C_LCD_Data &= ~(1<<LCD_RW);
	LCD_DATA4bit(charData);
}

void LCD_BacklightOn()
{
	I2C_LCD_Data |= (1<<LCD_BACKLIGHT);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	LCD_WriteCommand(command);
}

void LCD_WriteString(char *string)
{
	for (uint8_t i = 0; string[i]; i++)
	{
		LCD_WriteData(string[i]);
	}
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCD_GotoXY(row, col);
	LCD_WriteString(string);
}

void LCD_Init()
{
	I2C_Init();
	
	_delay_ms(20);
	LCD_WriteCommand(0x03);
	_delay_ms(5);
	LCD_WriteCommand(0x03);
	_delay_ms(1);
	LCD_WriteCommand(0x03);
	
	LCD_WriteCommand(0x02);
	
	LCD_WriteCommand(COMMAND_4_BIT_MODE);
	
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
	LCD_BacklightOn();
}

#endif