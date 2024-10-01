#include "I2C.h"
#include "LCD.h"
#include "USonic.h"
#include "DEF.h"

int main(void)
{
	uint8_t distance;
	
	sei();
	
	DDRD |= 0x08;
	DDRD &= 0xef;
	
	timerInit();
	
	uint8_t buff[30];
	
	LCD_Init();
	LCD_WriteStringXY(0,0,"Hello ATmega128a");
	
	while (1)
	{
		triggerPin();
		distance = meanDistance();
		
		sprintf(buff, "distance : %-5d", distance);
		LCD_WriteStringXY(1,0,buff);
		_delay_ms(1000);
	}
}

