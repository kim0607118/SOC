#include "I2C_LCD.h"

uint8_t I2C_LCD_Data;

void LCD_Data4bit(uint8_t data){
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | (data & 0xf0);
	LCD_EnablePin();
	I2C_LCD_Data = (I2C_LCD_Data & 0x0f) | ((data &0x0f) << 4);
	LCD_EnablePin();
}
void LCD_EnablePin(){
	I2C_LCD_Data &= ~(1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	I2C_LCD_Data |= (1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	I2C_LCD_Data &= ~(1<<LCD_E);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
	_delay_us(1600);
}
void LCD_WriteCommand(uint8_t commandData){
	I2C_LCD_Data &= ~(1<<LCD_RS);
	I2C_LCD_Data &= ~(1<<LCD_RW);
	LCD_Data4bit(commandData);
}
void LCD_WriteData(uint8_t charData){
	I2C_LCD_Data |= (1<<LCD_RS);
	I2C_LCD_Data &= ~(1<<LCD_RW);
	LCD_Data4bit(charData);
}
void LCD_BACKLIGHTOn(){
	I2C_LCD_Data |= (1<<LCD_BACKLIGHT);
	I2C_TxByte(LCD_DEV_ADDR, I2C_LCD_Data);
}
void LCD_GotoXY(uint8_t row, uint8_t col){
	col %= 16;
	row %= 2;
	uint8_t address = (0x40 * row) + col;	// 주소 계산
	uint8_t command = 0x80 + address;		// 커맨드 값 계산(주소설정)
	LCD_WriteCommand(command);				// 주소 커맨드를 전송
}
void LCD_WriteString(char *string){
	for (uint8_t i=0; string[i]; i++)
	{
		LCD_WriteData(string[i]);	// 문자열을 출력
	}
}
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string){
	LCD_GotoXY(row, col);
	LCD_WriteString(string);
}
void LCD_Init(){
	I2C_Init();
	
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
	LCD_BACKLIGHTOn();
}