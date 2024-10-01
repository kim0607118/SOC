/*
 * 20240524.c
 *
 * Created: 2024-05-23 오후 12:32:46
 * Author : PC1
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL

void delay_us(unsigned char time_us)
{
	register unsigned char i;
	for(i=0;i<time_us;i++) //4 cycle
	{
		asm volatile("PUSH R0"); //2 cycle
		asm volatile("POP R0"); //2 cycle
		asm volatile("PUSH R0"); //2 cycle
		asm volatile("POP R0"); //2 cycle
		asm volatile("PUSH R0"); //2 cycle
		asm volatile("POP R0"); //2 cycle
		// Sum = 16 cycle=1 us for 16MHz
	}
}
void delay_ms(unsigned int time_ms)
{
	register unsigned int i;
	for(i=0;i<time_ms;i++) //4 cycle
	{
		delay_us(250);
		delay_us(250);
		delay_us(250);
		delay_us(250);
	}
}
int main(void)
{
	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	//PORTD = 0xff;

	while(1)
	{
		PORTA = 0xff;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x01;	//0000 0001
		delay_ms(500);
		PORTA = 0x00;
		PORTB = 0xff;
		PORTC = 0x00;
		PORTD = 0x03;	//0000 0011
		delay_ms(500);
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0xff;
		PORTD = 0x07;	//0000 0111
		delay_ms(500);
		PORTA = 0xff;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x0f;
		delay_ms(500);
		PORTA = 0x00;
		PORTB = 0xff;
		PORTC = 0x00;
		PORTD = 0x1f;
		delay_ms(500);
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0xff;
		PORTD = 0x3f;
		delay_ms(500);
		PORTA = 0xff;
		PORTB = 0xff;
		PORTC = 0xff;
		PORTD = 0x7f;
		delay_ms(500);
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0xff;
		delay_ms(500);
	}
}
