/*
 * led.h
 *
 *  Created on: Sep 13, 2024
 *      Author: PC1
 */

#ifndef HW_DRIVER_LED_H_
#define HW_DRIVER_LED_H_

#include "hw_def.h"

void ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);

#endif /* HW_DRIVER_LED_H_ */
