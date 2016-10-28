/*
 * control.h
 *
 *  Created on: Oct 28, 2016
 *      Author: ikhatckevich
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdint.h>

#define F_MOT (400)

void control_init(void);
uint8_t control_setlocation(uint16_t l);


#endif /* CONTROL_H_ */
