/*
 * led.c
 *
 * Created: 2024-05-24 오전 9:43:07
 *  Author: PC1
 */ 
#include "led.h"
#include <avr/io.h>

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
