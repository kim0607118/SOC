#include "lcd.h"

void LCD_Data(uint8_t data)
{
	LCD_DATA_PORT = data;	// 데이터 핀에 8비트 출력
}

void LCD_Data4bit(uint8_t data)
{
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (data & 0xf0);
	LCD_EnablePin();
	//_delay_us(100);
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((data &0x0f) << 4);
	LCD_EnablePin();
}

void LCD_WritePin()
{
	LCD_RW_PORT &= ~(1<<LCD_RW);	// RW핀을 LOW로 설정하여 쓰기모드 진입
}

void LCD_EnablePin()
{
	LCD_E_PORT &= ~(1<<LCD_E);	// E핀을 LOW로 설정
	LCD_E_PORT |= (1<<LCD_E);	// E핀을 HIGH로 설정해서 동작 신호를 전송
	LCD_E_PORT &= ~(1<<LCD_E);	// E핀을 LOW로 설정
	_delay_us(1600);			// 1600 이상
}

void LCD_WriteCommand(uint8_t commandData)
{
	LCD_RS_PORT &= ~(1<<LCD_RS);	// RS핀을 LOW로 설정해서 명령어 모드로 진입
	LCD_WritePin();					// 데이터 쓰기모드 진입
	LCD_Data4bit(commandData);			// 명령어를 데이터핀에  출력
	//LCD_EnablePin();				// LCD 동작 신호 전송
}

void LCD_WriteData(uint8_t charData)
{
	LCD_RS_PORT |= (1<<LCD_RS);		// RS핀을 HIGH로 설정해서 문자 모드로 진입
	LCD_WritePin();					// 데이터 쓰기모드 진입
	LCD_Data4bit(charData);			// 명령어를 데이터핀에  출력
	//LCD_EnablePin();				// LCD 동작 신호 전송
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
	col %= 16;	// col을 16으로 제한
	row %= 2;	// row를 2로 제한
	uint8_t address = (0x40 * row) + col;	// 주소 계산
	uint8_t command = 0x80 + address;		// 커맨드 값 계산(주소설정)
	LCD_WriteCommand(command);				// 주소 커맨드를 전송
}

void LCD_WriteString(char *string)
{
	for (uint8_t i=0; string[i]; i++)
	{
		LCD_WriteData(string[i]);	// 문자열을 출력
	}
}

void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCD_GotoXY(row, col);
	LCD_WriteString(string);
}

void LCD_Init()
{
	LCD_DATA_DDR = 0xff;
	LCD_RS_DDR |= (1<<LCD_RS);
	LCD_RW_DDR |= (1<<LCD_RW);
	LCD_E_DDR |= (1<<LCD_E);
	
	_delay_ms(20);		// 초기화 시간 대기 (충분한 시간)
	LCD_WriteCommand(0x03);	//4bit 모드 설정
	_delay_ms(5);
	LCD_WriteCommand(0x03);	//4bit 모드 설정
	_delay_ms(5);
	LCD_WriteCommand(0x03);	//4bit 모드 설정
	LCD_WriteCommand(0x02);	//4bit 모드 설정
	
	LCD_WriteCommand(COMMAND_4_BIT_MODE);
	
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
}
