/*
 * 20240524-2.c
 *
 * Created: 2024-05-24 오후 12:27:36
 * Author : PC1
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC = 0xff;
	DDRD &= ~(1<<0);
	//PORTD |= (1<<0);
    /* Replace with your application code */
    while (1) 
    {
		if(PIND & (1<<0)){
			PORTC &= ~(1<<4);
		}
		else{
			PORTC |= (1<<4);
		}	
    }
}

