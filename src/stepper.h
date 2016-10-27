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
	volatile uint8_t phase; //номер текущей фазы (0-7)
	volatile uint16_t curPos; //текущая позиция (в шагах)
	uint16_t dstPos; //позиция назначения
	const int8_t fwdPhaseDir; //приращение фазы, соответствующее движению вперед (+/- 1)
	volatile uint8_t* ctlPort; //ссылка на порт (передается как &PORTx)
	const uint8_t ctlMask; //маска части порта (0x0F, 0xF0)
	//const uint8_t ctlOffset; //смещение... хз как объяснить. может выпилю к херам
}drvCtx;

void stepper_init (void);

/*
 * производит один шаг к позиции назначения
 * возвращает число шагов. 0 - если уже в позиции назначения
 * */
uint8_t stepper_do(drvCtx* drv);

#endif /* STEPPER_H_ */
