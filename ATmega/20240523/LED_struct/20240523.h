
/*
 * _20240523.h
 *
 * Created: 2024-05-24 오전 11:41:44
 *  Author: PC1
 */ 
#include <avr/io.h>
#ifndef a20240523_H_
#define a20240523_H_

typedef struct{
	volatile uint8_t	*port;
	uint8_t				pinNumber;
}LED_t;

void ledOn(LED_t *led);
void ledInit(LED_t *led);
void ledOff(LED_t *led);

#endif