/*
 * led_8.c
 *
 * Created: 2024-05-23 오후 4:14:28
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
	DDRB = 0xff;
	const uint8_t led_pattern[] = {
		0b00000001,
		0b00000011,
		0b00000111,
		0b00001111,
		0b00011111,
		0b00111111,
		0b01111111};

	while(1)
	{
		
		for(int i =0; i<sizeof(led_pattern)/sizeof(led_pattern[0]);i++){
			PORTB = led_pattern[i];
			delay_ms(100);
		}
		/*
		for (uint8_t i = 0; i<4; i++){
			PORTB = ((0x01 << i)|(0x80 >> i));
			delay_ms(500);
		}
		for (uint8_t i = 1; i<3; i++){
			PORTD = ((0x08 >> i)|(0x10 << i));
			delay_ms(500);
		}
		*/
	}
}
