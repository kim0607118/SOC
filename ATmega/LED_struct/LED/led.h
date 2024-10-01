
/*
 * led.h
 *
 * Created: 2024-05-24 오전 9:42:49
 *  Author: PC1
 */ 
#include <avr/io.h>
#ifndef LED_H_
#define LED_H_
#include <util/delay.h>

#define LED_DDR		DDRD
#define LED_PORT	PORTD

void ledInit();
void GPIO_Output(uint8_t data);
void ledLeftShift(uint8_t *data);
void ledRightShift(uint8_t *data);

#endif