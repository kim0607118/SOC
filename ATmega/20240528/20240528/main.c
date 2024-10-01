#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<DDRB4);
	//TCCR0 = 0x1C;
    //TCCR0 |= (1<<WGM01);
	//TCCR0 |= (1<<COM00);
	//TCCR0 |= (1<<CS02);
	TCCR0 |= (1<<WGM01) | (1<<COM00) | (1 << CS02) | (1 << CS01);
	OCR0 = 124;
	
    while (1) 
    {
		//OCF0 값이 0인지 확인
		while((TIFR & 0x02)==0){
			TIFR = 0x02;
			OCR0 = 124;
		}
    }
}
