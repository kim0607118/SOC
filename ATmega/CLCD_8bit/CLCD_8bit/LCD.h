#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define LCD_DATA_DDR	DDRF
#define LCD_DATA_PORT	PORTF
#define LCD_DATA_PIN	PINF
#define LCD_RS_DDR		DDRE
#define LCD_RW_DDR		DDRE
#define LCD_E_DDR		DDRE
#define LCD_RS_PORT		PORTE
#define LCD_RW_PORT		PORTE
#define LCD_E_PORT		PORTE
#define LCD_RS			7
#define LCD_RW			6
#define LCD_E			5

#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_DISPLAY_ON		0x0C
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_ENTRY_MODE		0x06
#define COMMAND_8_BIT_MODE		0x38
#define COMMAND_4_BIT_MODE		0x28

void LCD_Data(uint8_t data);
//void LCD_Data4bit(uint8_t data);
void LCD_WritePin();
void LCD_ReadPin();
void LCD_EnablePin();
void LCD_WriteCommand(uint8_t commandData);
void LCD_WriteData(uint8_t charData);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteString(char *string);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *sting);
void LCD_Init();




#endif /* LCD_H_ */