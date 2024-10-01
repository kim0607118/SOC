/*
 * button.c
 *
 * Created: 2024-05-27 오전 11:39:11
 *  Author: PC1
 */ 
#include "./button.h"


void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber){
	button ->ddr = ddr;
	button ->pin = pin;
	button ->btnPin = pinNumber;
	button ->prevState = RELEASED;
	*button ->ddr &= ~(1<<button->btnPin);
}

uint8_t Button_getState(Button *button){
	uint8_t curState = *button->pin & (1<<button->btnPin);
	if((curState==PUSHED)&&(button->prevState==RELEASED)){
		_delay_ms(50);
		button->prevState=PUSHED;
		return ACT_PUSHED;
	}
	else if((curState!=PUSHED)&&(button->prevState==PUSHED)){
		_delay_ms(50);
		button->prevState=RELEASED;
		return ACT_RELEASE;
	}
	return NO_ACT;
}
