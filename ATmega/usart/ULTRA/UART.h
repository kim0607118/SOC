#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

/*
void UART0_Init();
void UART0_Transmit(char data);
unsigned UART0_Receive();
*/

void UART0_Init(){
	UBRR0H = 0;
	UBRR0L = 207;
	
	UCSR0A |= (1<<U2X0);
	UCSR0C |= 0x06;
	
	UCSR0B |= (1<<RXEN0);
	UCSR0B |= (1<<TXEN0);
	
	UCSR0B |= (1<<RXCIE0);
}

void UART0_Transmit(char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UART0_Receive(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

#endif