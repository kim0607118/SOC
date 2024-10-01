#include <avr/io.h>
#include <util/delay.h>
#include "./driver/button.h"


int main(void)
{
	LED_DDR = 0xff;
	Button BtnOn;
	Button BtnOFF;
	Button BtnToggle;
	
	Button_Init(&BtnOn,&Button_DDR,&Button_PIN,Button_ON);
	Button_Init(&BtnOFF,&Button_DDR,&Button_PIN,Button_OFF);
	Button_Init(&BtnToggle,&Button_DDR,&Button_PIN,Button_Toggle);
    /* Replace with your application code */
    while (1) 
    {
		if(Button_getState(&BtnOn) == ACT_RELEASE){
			LED_PORT = 0xff;
		}
		if(Button_getState(&BtnOFF) == ACT_RELEASE){
			LED_PORT = 0x00;
		}
		if(Button_getState(&BtnToggle) == ACT_RELEASE){
			LED_PORT ^= 0xff;
		}
    }
}

