/*
 * main.c
 *
 * Created: 2024-05-24 오전 11:42:47
 *  Author: PC1
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include "../20240523/led.h"
#include "20240523.h"

int main(void)
{
	LED_t led;
	led.port = &PORTA;
	led.pinNumber = 0;
	
	ledInit(&led);
	
	/* Replace with your application code */
	while (1)
	{
		ledOn(&led);
		_delay_ms(500);
		ledOff(&led);
		_delay_ms(500);
	}
}
