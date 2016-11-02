/*
 * uart.h
 *
 *  Created on: Nov 2, 2016
 *      Author: ikhatckevich
 */

#ifndef UART_H_
#define UART_H_
#include <stdio.h>

#define DAUD_RATE (115200)

void uart_init(void);
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);
#endif /* UART_H_ */
