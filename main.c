/*
 * main.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */
#include "src/control.h"
#include <util/delay.h>

int main (void){
	_delay_ms(2000);
	control_init();
	control_setlocation(4096);
	while (1);
	return 0;
}
