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
	while (1){
		control_setlocation(4096, 590);
		_delay_ms(10000);
		control_setlocation(0, 4096);
		_delay_ms(10000);
	}
	return 0;
}
