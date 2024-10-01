/*
 * 20240527.c
 *
 * Created: 2024-05-27 오전 9:16:28
 * Author : PC1
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0xff;
	//DDRD |= ~(1<<DDRD0);	//ddrd = 0b1111110
	DDRD = 0xf0;			// 1111 1000
	uint8_t ledData = 0x01;
	uint8_t buttonData;		//button input
	int flag = 0;
	PORTC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		 buttonData = PIND;
		 if((buttonData&(1<<0))==0){
			 PORTC = ledData;
			 ledData = (ledData>>7)|(ledData<<1);
			 _delay_ms(300);
		 }
		 if((buttonData&(1<<1))==0){
			 PORTC = ledData;
			 ledData = (ledData>>1)|(ledData<<7);
			 _delay_ms(300);
		 }
		 if((buttonData&(1<<2))==0){
			 for(uint8_t i=0;i<3;i++){
				 PORTC = 0xff;
				 _delay_ms(300);
				 PORTC = 0x00;
				 _delay_ms(300);
			 }
		 }
    }
}

