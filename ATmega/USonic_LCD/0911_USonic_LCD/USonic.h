#ifndef USonic_H_
#define USonic_H_

#include "DEF.h"

void timerInit()
{
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

void triggerPin()
{
	PORTD &= ~(1<<PORTD3);
	_delay_us(1);
	PORTD |= (1<<PORTD3);
	_delay_us(10);
	PORTD &= ~(1<<PORTD3);
}

uint8_t meanDistance()
{
	TCNT1 = 0;
	while(!(PIND & 0x10))
	{
		if(TCNT1 > 65000)
		{
			return;
		}
	}
	TCNT1 = 0;
	while(PIND & 0x10)
	{
		if(TCNT1 > 65000)
		{
			TCNT1 = 0;
			break;
		}
	}
	double pluseWidth = 1000000.0 * TCNT1 * 1024 / 16000000;	
	return pluseWidth / 58;
}

#endif