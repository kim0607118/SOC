/*
 * interrupt.c
 *
 * Created: 2024-05-24 오후 4:31:37
 * Author : PC1
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_DDR		DDRC
#define LED_PORT	PORTC

void ledInit(){
	LED_DDR = 0xff;
}

void GPIO_Output(uint8_t data){
	LED_PORT = data;
	_delay_ms(1000);
}

void ledLeftShift(uint8_t *data){
	*data = (*data) | (*data << 1);
	GPIO_Output(*data);
}

void ledRightShift(uint8_t *data){
	*data = (*data >> 1) & (*data);
	GPIO_Output(*data);
}

ISR(INT0_vect){
	ledInit();
	uint8_t ledData = 0x01;
	GPIO_Output(ledData);
	
	for(uint8_t i=0; i<7; i++){
		ledLeftShift(&ledData);
	}
	for(uint8_t i=0; i<7; i++){
		ledRightShift(&ledData);
	}
}


int main(void)
{	
	DDRC = 0xff;	//set portc output
	sei();			//enable interrupt
	EICRA = 0x01;	//use int0 under edge
	EIMSK = 0x01;	//enable int0 interrupt
	
	DDRD = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTC = 0x00;
    }
}

