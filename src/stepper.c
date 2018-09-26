/*
 * stepper.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */

#include "stepper.h"
#include <avr/pgmspace.h>

const PROGMEM uint8_t phaseMap[] = {
//		  ABCDABCD
		0b10011001,
		0b10001000,
		0b11001100,
		0b01000100,
		0b01100110,
		0b00100010,
		0b00110011,
		0b00010001
};

uint8_t stepper_do(drvCtx* drv){
	if (drv->curPos == drv->dstPos) return 0;
	if (drv->dstPos > drv->curPos){
		//move forward
		drv->curPos++;
		drv->phase += drv->fwdPhaseDir; //инкремент фазы с поправкой на ориентацию двигателя
	}else{
		//move backward
		drv->curPos--;
		drv->phase -= drv->fwdPhaseDir;
	}
	//выводим в порт новое состояние фаз двигателя
	*drv->ctlPort = (*drv->ctlPort & ~drv->ctlMask) | (pgm_read_byte(&phaseMap[drv->phase & 7]) & drv->ctlMask);
	return 1;
}
