/*
 * draw.c
 *
 *  Created on: Nov 22, 2016
 *      Author: ikhatckevich
 */


#include "draw.h"
#include "control.h"
#include <stdlib.h>

void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	//see https://hubstub.ru/programming/47-risovanie-geometricheskih-figur-natftdisplee-na-primeressd1289.html
	int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    //setPixel(x2, y2);
    while(x1 != x2 || y1 != y2)
   {
        control_move(x1, y1);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}
void draw_circle(uint16_t x, uint16_t y, uint16_t r){

}
