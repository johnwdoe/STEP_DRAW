/*
 * main.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */
#include "src/control.h"
#include "src/uart.h"
#include <util/delay.h>
#include <stdio.h>

static FILE uartio = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

int main (void){
	//TODO see http://mainloop.ru/avr-atmega/avr-uart-fifo-irq.html
	stdout = &uartio;
	stdin = &uartio;

	_delay_ms(2000);
	control_init();
	uart_init();

	printf("INITIALIZED\n");
	while (1){

		control_setlocation(4096, 590);
		_delay_ms(10000);
		control_setlocation(0, 4096);
		_delay_ms(10000);
	}
	return 0;
}
