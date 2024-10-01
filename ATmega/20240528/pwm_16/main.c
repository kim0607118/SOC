#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<DDRB5);
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	TCCR1C = 0;
	
	ICR1 = 2499;
	OCR1A = 625;
    /* Replace with your application code */
    while (1) 
    {
    }
}

