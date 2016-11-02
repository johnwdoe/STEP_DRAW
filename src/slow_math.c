/*
 * slow_math.c
 *
 *  Created on: Nov 1, 2016
 *      Author: ikhatckevich
 */

#include "slow_math.h"

uint32_t slow_pwr2 (uint16_t d){
	uint32_t res = 0;
	uint16_t iter = d;
	while(iter--) res+=d;
	return res;
}

uint16_t slow_sqrt (uint32_t d){
	uint32_t res = 0;
	uint32_t temp;
	uint32_t mask = 0x40000000;
	do{
		temp = res | mask;
		res >>= 1;
		if( temp <= d ){
			res |= mask;
			d -= temp;
		}
	}while( mask >>= 2 );
	if( res < d && res < 0xFFFF ) ++res; // ���������� ����������
	return (uint16_t)res;
}