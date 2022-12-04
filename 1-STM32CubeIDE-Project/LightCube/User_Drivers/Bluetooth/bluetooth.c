/*
 * bluetooth.c
 *
 *  Created on: Nov 1, 2022
 *      Author: Matrix
 */
#include "bluetooth.h"
void BT_printf(char *fmt, ...){
	char buffer[USART_REC_LEN+1];
	uint16_t txLen = 0;
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, USART_REC_LEN+1, fmt, args);
	txLen = strlen(buffer);
	if(txLen>USART_REC_LEN) txLen = USART_REC_LEN;
	HAL_UART_Transmit(&huart6, (uint8_t *)buffer, txLen, HAL_MAX_DELAY);
	va_end(args);
}


