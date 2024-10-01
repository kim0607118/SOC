#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<DDRD5);
	PORTD &= ~(1<<PORTD5);
	TCCR0 |= (1<<CS02) | (1<<CS00);
	TCNT0 =  6;
    /* Replace with your application code */
    while (1) 
    {
		while ((TIFR & 0x01)==0);
		PORTD = ~PORTD;
		TCNT0 = 131;
		TIFR = 0x01;
    }
}