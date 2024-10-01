#include "UART.h"

int main(void)
{
	UART0_Init();
	
	while (1)
	{
		UART0_Transmit(UART0_Receive());
	}
}