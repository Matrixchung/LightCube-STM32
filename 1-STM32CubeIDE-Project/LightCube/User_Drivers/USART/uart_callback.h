/*
 * uart_callback.h
 *
 *  Created on: Oct 26, 2022
 *      Author: Matrix
 */

#ifndef USART_UART_CALLBACK_H_
#define USART_UART_CALLBACK_H_

#include "main.h"
#include <string.h>
#include "retarget.h"

extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

#define RETURN_ON_RECEIVE 0

#define USART1_REC_LEN 200
//#define USART2_REC_LEN 200
#define USART6_REC_LEN 200

extern uint8_t USART1_RX_BUF[USART1_REC_LEN];
extern uint16_t USART1_RX_STA;
extern uint8_t USART1_NewData;

//extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];
//extern uint16_t USART2_RX_STA;
//extern uint8_t USART2_NewData;

extern uint8_t USART6_RX_BUF[USART6_REC_LEN];
extern uint16_t USART6_RX_STA;
extern uint8_t USART6_NewData;

void UART1_SetCallback(void);
//void UART2_SetCallback(void);
void UART6_SetCallback(void);
void UART1_Clear(void);
//void UART2_Clear(void);
void UART6_Clear(void);
uint16_t UART1_ReceivedLength(void);
//uint16_t UART2_ReceivedLength(void);
uint16_t UART6_ReceivedLength(void);
uint8_t UART1_Available(void);
//uint8_t UART2_Available(void);
uint8_t UART6_Available(void);
uint8_t UART1_Read(uint8_t index);
//uint8_t UART2_Read(uint8_t index);
uint8_t UART6_Read(uint8_t index);
uint8_t* UART1_GetBufferPtr(void);
//uint8_t* UART2_GetBufferPtr(void);
uint8_t* UART6_GetBufferPtr(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif /* USART_UART_CALLBACK_H_ */
