#include "I2C_LCD.h"

int main(void)
{
	uint16_t count = 0;
	uint8_t buff[30];
	
	LCD_Init();
	LCD_WriteStringXY(0,0,"Hello Atmega128");
	
    while (1) 
    {
		sprintf(buff,"count : %-5d", count++);
		LCD_WriteStringXY(1,0,buff);
		_delay_ms(200);
    }
}

