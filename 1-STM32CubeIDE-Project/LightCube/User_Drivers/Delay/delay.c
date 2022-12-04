/*
 * delay.c
 *
 *  Created on: Oct 25, 2022
 *      Author: Matrix
 */
#include "delay.h"
void delay_us(uint32_t us){
	uint32_t delay = (HAL_RCC_GetHCLKFreq() / 8000000 * us);
	do{__NOP();}while(delay--);
}
void delay_ms(uint32_t ms){
    while(ms--){delay_us(1000);}
}
