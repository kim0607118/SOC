#include "UART.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

void timerInit(){
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

void triggerPin(){
	PORTD &= ~(1<<PORTD1);
	_delay_us(1);
	PORTD |= (1<<PORTD1);
	_delay_us(10);
	PORTD &= ~(1<<PORTD1);
}

uint8_t meanDistance(){
	TCNT1 = 0;
	while(!(PIND & 0x01))
	{
		if(TCNT1 > 65000)
		{
			return;
		}
	}
	TCNT1 = 0;
	while(PIND & 0x01)
	{
		if(TCNT1 > 65000)
		TCNT1 = 0;
		break;
	}
}

int main(void)
{
	uint8_t distance;

	stdout = &OUTPUT;

	UART0_Init();
	sei();

	DDRD |= 0x02;
	DDRD &= 0xfe;
	
	timerInit();
	
    while (1) 
    {
		triggerPin();
		distance = meanDistance();
		printf("Distance : %d cm\r\n", distance);
		_delay_ms(1000);
    }
}