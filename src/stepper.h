/*
 * stepper.h
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdio.h>

typedef struct {
	uint8_t phase;
	uint16_t curPos;
	uint16_t destPos;
	volatile uint8_t* ctlPort;
	const uint8_t ctlMask;
	const uint8_t ctlOffset;
}drvCtx;

#endif /* STEPPER_H_ */
