/*
 * stepper.h
 *
 *  Created on: Oct 27, 2016
 *      Author: ikhatckevich
 *
 *  Библиотечка умеет либо шагать, либо нихуя
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>

typedef struct {
	volatile uint8_t phase; //номер текущей фазы (0-7)
	volatile uint16_t curPos; //текущая позиция (в шагах)
	volatile uint16_t dstPos; //позиция назначения
	const int8_t fwdPhaseDir; //приращение фазы, соответствующее движению вперед (+/- 1)
	volatile uint8_t* ctlPort; //ссылка на порт (передается как &PORTx)
	const uint8_t ctlMask; //маска части порта (0x0F, 0xF0)
}drvCtx;

/*
 * производит один шаг к позиции назначения
 * возвращает число шагов. 0 - если уже в позиции назначения
 * */
uint8_t stepper_do(drvCtx* drv);

#endif /* STEPPER_H_ */
