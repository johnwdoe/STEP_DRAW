/*
 * draw.c
 *
 *  Created on: Nov 22, 2016
 *      Author: ikhatckevich
 */


#include "draw.h"
#include "control.h"

void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	//see https://hubstub.ru/programming/47-risovanie-geometricheskih-figur-natftdisplee-na-primeressd1289.html
	uint16_t deltaX = (x2 > x1) ? x2 - x1 : x1 - x2;
	uint16_t deltaY = (y2 > y1) ? y2 - y1 : y1 - y2;
	int8_t signX = x1 < x2 ? 1 : -1;
	int8_t signY = y1 < y2 ? 1 : -1;
	int16_t error = deltaX - deltaY;
	int16_t error2;
	for(;;){
		if (control_move(x1, y1) == CONTROL_NOINIT) return;
		if (x1 == x2 && y1 == y2) break;
		error2 = error*2;
		if(error2 > -deltaY){
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX){
			error += deltaX;
			y1 += signY;
		}
	}
}
void draw_circle(uint16_t x, uint16_t y, uint16_t r){

}
