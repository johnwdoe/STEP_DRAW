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
	volatile uint8_t phase; //����� ������� ���� (0-7)
	volatile uint16_t curPos; //������� ������� (� �����)
	uint16_t dstPos; //������� ����������
	const int8_t fwdPhaseDir; //���������� ����, ��������������� �������� ������ (+/- 1)
	volatile uint8_t* ctlPort; //������ �� ���� (���������� ��� &PORTx)
	const uint8_t ctlMask; //����� ����� ����� (0x0F, 0xF0)
	//const uint8_t ctlOffset; //��������... �� ��� ���������. ����� ������ � �����
}drvCtx;

void stepper_init (void);

/*
 * ���������� ���� ��� � ������� ����������
 * ���������� ����� �����. 0 - ���� ��� � ������� ����������
 * */
uint8_t stepper_do(drvCtx* drv);

#endif /* STEPPER_H_ */
