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
	uint16_t t1, t2, t3;
	char cmd;
	stdout = &uartio;
	stdin = &uartio;

	_delay_ms(2000);
	control_init();
	uart_init();

	printf("DIS = ");
	scanf("%u", &t3);
	printf("%u\nACT (l1 l2) = ", t3);
	scanf("%u%u", &t1, &t2);
	control_setactualcoords(t1, t2, t3);
	printf("(%u %u)\n", t1, t2);

	while (1){
		printf ("CMD: C X Y = ");
		scanf("%s%u%u", &cmd, &t1, &t2);
		//control_setxy(t1, t2);
		switch (cmd){
		case 'D':
		case 'd':
			control_setxy(t1, t2);
			printf("%s %u %u SENT TO DRV AS DECART\n", &cmd, t1, t2);
			break;
		case 'L':
		case 'l':
			control_setlocation(t1, t2);
			printf("%s %u %u SENT TO DRV AS LINE\n", &cmd, t1, t2);
			break;
		case 'S':
		case 's':
			control_setactualcoords(t1, t2, t3);
			printf("NEW LOCATION %u %u SET. DIS = %u", t1, t2, t3);
			break;
		default:
			printf("ERR\n");
			break;
		}
	}

	return 0;
}
