/*
 * stepper.c
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 */

#include "stepper.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

const PROGMEM uint8_t phaseMap[] = {
		0b10011001,
		0b10001000,
		0b11001100,
		0b01000100,
		0b01100110,
		0b00100010,
		0b00110011,
		0b00010001
};

drvCtx drvArr[] = {
		{0, 0, 0, 1, &PORTC, 0x0F},
		{0, 0, 0, -1, &PORTC, 0xF0}
};

uint8_t stepper_do(drvCtx* drv){
	if (drv->curPos == drv->dstPos) return 0;
	if (drv->dstPos > drv->curPos){
		//move forward
		drv->curPos++;
		drv->phase += drv->fwdPhaseDir; //��������� ���� � ��������� �� ���������� ���������
	}else{
		//move backward
		drv->curPos--;
		drv->phase -= drv->fwdPhaseDir;
	}
	*drv->ctlPort = (*drv->ctlPort & ~drv->ctlMask) | (pgm_read_byte(&phaseMap[drv->phase & 7]) & drv->ctlMask);
	return 1;
}
