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

#define CONTROL_OK (0)
#define CONTROL_NOINIT (1)
#define CONTROL_BUSY (2)
#define CONTROL_OUTOFAREA (3)

/*
 * init GPIO, timers & etc*/
void control_hw_init(void);

/*
 * set initial geometry coordinates
 * and set carriage (x,y) to (d/2,d/2)*/
uint8_t control_init(uint16_t l1, uint16_t l2, uint16_t d);

/*
 * move carriage to (x,y)*/
uint8_t control_move(uint16_t x, uint16_t y);

/*
 * set relative l, r length
 */

uint8_t control_correct (uint16_t l1, uint16_t l2);
#endif /* CONTROL_H_ */
