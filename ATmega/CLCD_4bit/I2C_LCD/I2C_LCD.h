#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "I2C.h"

#define LCD_RS			0
#define LCD_RW			1
#define LCD_E			2
#define LCD_BACKLIGHT	3
#define LCD_DEV_ADDR	(0x27<<1)

#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_DISPLAY_ON		0x0C
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_ENTRY_MODE		0x06
#define COMMAND_4_BIT_MODE		0x28

void LCD_Data4bit(uint8_t data);
void LCD_EnablePin();
void LCD_WriteCommand(uint8_t commandData);
void LCD_WriteData(uint8_t charData);
void LCD_BACKLIGHTOn();
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteString(char *string);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);
void LCD_Init();

#endif