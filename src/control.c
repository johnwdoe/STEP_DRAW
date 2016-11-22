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
#include "slow_math.h"

#define T_DIV	(F_CPU/1024/F_MOT - 1)
#define T_START	(TCCR2 |= (7<<CS20))
#define T_STOP	(TCCR2 &= ~(7<<CS20))
#define F_BUSY	(1)
#define F_INITIALIZED (2)

volatile uint8_t flags = 0x00;
volatile uint16_t distance = 0;
drvCtx d1 = {0,0,0,1,&PORTC,0x0F};
drvCtx d2 = {0,0,0,-1,&PORTD,0xF0};

void control_hw_init(void){
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

uint8_t control_init(uint16_t l1, uint16_t l2, uint16_t d){
	flags &= ~F_BUSY; //reset busy flag
	d1.curPos = d1.dstPos = l1;
	d2.curPos = d2.dstPos = l2;
	distance = d;
	flags |= F_INITIALIZED;
	return CONTROL_OK;
}

uint8_t control_move(uint16_t x, uint16_t y){
	if (!(flags&F_INITIALIZED)) return CONTROL_NOINIT;
	if (x > distance) return CONTROL_OUTOFAREA;
	while (flags&F_BUSY); //тупим
	d1.dstPos = slow_sqrt(slow_pwr2(x) + slow_pwr2(y));
	d2.dstPos = slow_sqrt(slow_pwr2(distance - x) + slow_pwr2(y));
	flags |= F_BUSY; //погнали
	return CONTROL_OK;
}

ISR(TIMER2_COMP_vect){
	if (flags & F_BUSY){
		if ((stepper_do(&d1) | stepper_do(&d2)) == 0) flags ^= F_BUSY; //toggle to 0
	}
}
