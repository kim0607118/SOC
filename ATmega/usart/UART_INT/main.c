#include "UART.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

char rxBuff[100] = {0};
uint8_t rxFlag = 0;
	
ISR(USART0_RX_vect)
{
	static uint8_t rxHead = 0;
	uint8_t rxData = UDR0;
	
	if(rxData == '\n' || rxData == '\r')
	{
		
	}
}

int main(void)
{
	UART0_Init();
	uint8_t rxData;
	stdout = &OUTPUT;
	
	sei();
	
    while (1) 
    {
		rxFlag = 0;
		printf(rxBuff);
    }
}

