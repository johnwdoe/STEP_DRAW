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
//#include <math.h>
#include "slow_math.h"

#define T_DIV	(F_CPU/1024/F_MOT - 1)
#define T_START	(TCCR2 |= (7<<CS20))
#define T_STOP	(TCCR2 &= ~(7<<CS20))
#define F_BUSY	(1)

volatile uint8_t flags = 0x00;
uint16_t distance = 0;
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

uint8_t control_setlocation(uint16_t l1, uint16_t l2){
	if (flags & F_BUSY) return 0xFF; //если есть уже чем заняться, то игнорим
	drives[0].dstPos = l1;
	drives[1].dstPos = l2;
	flags |= F_BUSY; //даем понять, что можно крутить педали
	return 0;
}

uint8_t control_setxy(uint16_t x, uint16_t y){
	if (x > distance) return 0xFF; //impossible o_O
	//convert x,y to l1, l2
	//x= sqr(xx+yy)
	uint16_t l1, l2;
	//uint32_t tmp = (x*x + y*y);
	l1 = slow_sqrt(slow_pwr2(x) + slow_pwr2(y));
	//tmp = ((distance-x)*(distance-x) + y*y);
	l2 = slow_sqrt(slow_pwr2(distance-x) + slow_pwr2(y));
	return control_setlocation(l1, l2);
}

void control_setactualcoords(uint16_t l1, uint16_t l2, uint16_t d){
	//reset busy flag
	flags &= ~(F_BUSY);
	drives[0].curPos = l1;
	drives[0].dstPos = l1;
	drives[1].curPos = l2;
	drives[1].dstPos = l2;
	distance = d;
}

ISR(TIMER2_COMP_vect){
	if (flags & F_BUSY){
		if ((stepper_do(drives) | stepper_do(drives+1)) == 0) flags ^= F_BUSY; //toggle to 0
	}
}
