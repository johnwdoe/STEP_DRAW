/*
 * uart.c
 *
 *  Created on: Nov 2, 2016
 *      Author: ikhatckevich
 */

#include "uart.h"
#include <stdio.h>
#include <avr/io.h>

#define UBRR_ (F_CPU/16/BAUD_RATE - 1)

void uart_init(void){
	uint16_t ubrr = UBRR_;
	DDRD |= (1<<PD1); //TX PIN
	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL = (uint8_t)ubrr;
	UCSRB |= (1<<RXEN | 1<<TXEN);
	UCSRC = (1<<URSEL | 1<<UCSZ1 | 1<<UCSZ0);
}

int uart_putchar(char c, FILE *stream){
	//send
	while (!(UCSRA & (1<<UDRE))); //wait for empty buffer
	UDR = c;
	return 0;
}

uint8_t uart_getchar(FILE *stream){
	while (! (UCSRA & (1<<RXC)));
	return UDR;
}
