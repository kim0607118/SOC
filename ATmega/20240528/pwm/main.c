/*
 * pwm.c
 *
 * Created: 2024-05-28 오후 3:29:35
 * Author : PC1
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<DDRB4);
	TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS02);
	OCR0 = 64;
    /* Replace with your application code */
    while (1) 
    {
		/*
		for(uint8_t i = 0; i < 255; i++){
			OCR0 = i;
			_delay_ms(1);
		}
		*/
    }
}

