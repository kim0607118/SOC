/*
 * 20240523.c
 *
 * Created: 2024-05-24 오전 8:59:07
 * Author : PC1
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main(void)
{
	ledInit();
	uint8_t ledData = 0x01;
	GPIO_Output(ledData);
    /* Replace with your application code */
    while (1) 
    {
		for(uint8_t i=0; i<7; i++){
			ledLeftShift(&ledData);
		}
		for(uint8_t i=0; i<7; i++){
			ledRightShift(&ledData);
		}
    }
}

