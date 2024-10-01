#include <avr/io.h>
#define F_CPU 16000000UL
#include "../20240523/led.h"
#include "20240523.h"

void ledInit(LED_t *led){
	*(led->port-1) |= (1<<led->pinNumber);
}

void ledOn(LED_t *led){
	*(led->port) |= *(led->port)|(1<<led->pinNumber);
}

void ledOff(LED_t *led){
	*(led->port) &= ~(1<<led->pinNumber);
}

