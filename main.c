/*
 * main.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */
#include "src/control.h"
#include "src/uart.h"
#include "src/draw.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

static FILE uartio = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

int main (void){
	uint16_t t1, t2, t3, t4;
	//uint16_t t1s, t2s;
	char cmd;
	stdout = &uartio;
	stdin = &uartio;

	_delay_ms(2000);
	control_hw_init();
	uart_init();

	printf_P(PSTR("DISTANCE = "));
	scanf_P(PSTR("%u"), &t3);
	printf_P(PSTR("%u\nACT (l1 l2) = "), t3);
	scanf_P(PSTR("%u%u"), &t1, &t2);
	control_init(t1, t2, t3);
	printf_P(PSTR("(%u %u)\n"), t1, t2);

	while (1){
		printf_P(PSTR("Waiting for command...\n"));
		scanf_P(PSTR("%s"), &cmd);
		switch (cmd){
		case 'm':
			scanf_P(PSTR("%u%u"), &t1, &t2);
			control_move(t1, t2);
			printf_P(PSTR("OK\n"));
			break;
		case 'l':
			scanf_P(PSTR("%u%u%u%u"), &t1, &t2, &t3, &t4);
			printf_P(PSTR("Try to draw line (%u, %u) - (%u, %u)...\n"), t1, t2, t3, t4);
			draw_line(t1, t2, t3, t4);
			printf_P(PSTR("OK\n"));
			break;
		case 'c':
			scanf_P(PSTR("%u%u%u"), &t1, &t2, &t3);
			draw_circle(t1, t2, t3);
			printf_P(PSTR("OK\n"));
			break;
		case 'f':
			scanf_P(PSTR("%u%u"), &t1, &t2);
			control_correct(t1, t2);
			printf_P(PSTR("OK\n"));
			break;
		default:
			printf_P(PSTR("ERR\n"));
			break;
		}
	}

	return 0;
}
