/*
 * control.c
 *
 *  Created on: Oct 28, 2016
 *      Author: ikhatckevich
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "control.h"
#include "stepper.h"

#define T_DIV	(F_CPU/1024/F_MOT - 1)
#define T_START	(TCCR2 |= (7<<CS20))
#define T_STOP	(TCCR2 &= ~(7<<CS20))
#define F_BUSY	(1)

volatile uint8_t flags = 0x00;
drvCtx drives[] = {
		{0, 0, 0, 1, &PORTC, 0x0F},
		{0, 0, 0, -1, &PORTD, 0xF0}
};

void control_init(void){
	DDRC |= 0x0F;
	DDRD |= 0xF0;
	//initialize 8-bit timer 2 to f = F_MOT
	TCCR2 = (1<<WGM21 /*CTC - mode*/);
	OCR2 = (uint8_t) T_DIV;
	//configure compare-interrupt
	TIMSK |= (1<<OCIE2);
	T_START;
	sei();
}

uint8_t control_setlocation(uint16_t l){
	if (flags & F_BUSY) return 0xFF; //если есть уже чем заняться, то игнорим
	drives[0].dstPos = l;
	flags |= F_BUSY; //даем понять, что можно крутить педали
	return 0;
}

void control_setactualcoords(uint16_t l){
	//reset busy flag
	flags &= ~(F_BUSY);
	drives[0].curPos = l;
	drives[0].dstPos = l;
}

ISR(TIMER2_COMP_vect){
	if (flags & F_BUSY){
		if (stepper_do(drives) == 0) flags ^= F_BUSY; //toggle to 0
	}
}
