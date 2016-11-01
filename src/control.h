/*
 * control.h
 *
 *  Created on: Oct 28, 2016
 *      Author: ikhatckevich
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdint.h>

#define F_MOT (500)

void control_init(void);
uint8_t control_setlocation(uint16_t l1, uint16_t l2);
uint8_t control_setxy(uint16_t x, uint16_t y);
void control_setactualcoords(uint16_t l1, uint16_t l2, uint16_t d);


#endif /* CONTROL_H_ */
