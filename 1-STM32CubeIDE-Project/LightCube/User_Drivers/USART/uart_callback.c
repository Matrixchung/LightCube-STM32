/*
 * uart_callback.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Matrix
 */
#include "uart_callback.h"
#ifdef USART_UART_CALLBACK_H_

uint8_t USART1_RX_BUF[USART1_REC_LEN];
uint16_t USART1_RX_STA=0;
uint8_t USART1_NewData;

//uint8_t USART2_RX_BUF[USART2_REC_LEN];
//uint16_t USART2_RX_STA=0;
//uint8_t USART2_NewData;

uint8_t USART6_RX_BUF[USART6_REC_LEN];
uint16_t USART6_RX_STA=0;
uint8_t USART6_NewData;

void UART1_SetCallback(void){ HAL_UART_Receive_DMA(&huart1, (uint8_t *)&USART1_NewData, 1); }
//void UART2_SetCallback(void){ HAL_UART_Receive_IT(&huart2, (uint8_t *)&USART2_NewData, 1); }
void UART6_SetCallback(void){ HAL_UART_Receive_DMA(&huart6, (uint8_t *)&USART6_NewData, 1); }
void UART1_Clear(void){ USART1_RX_STA = 0; }
//void UART2_Clear(void){ USART2_RX_STA = 0; }
void UART6_Clear(void){ USART6_RX_STA = 0; }
uint16_t UART1_ReceivedLength(void){ return USART1_RX_STA&0x3FFF; }
//uint16_t UART2_ReceivedLength(void){ return USART2_RX_STA&0x3FFF; }
uint16_t UART6_ReceivedLength(void){ return USART6_RX_STA&0x3FFF; }
uint8_t UART1_Available(){ return USART1_RX_STA&0xC000?1:0; }
//uint8_t UART2_Available(){ return USART2_RX_STA&0xC000?1:0; }
uint8_t UART6_Available(){ return USART6_RX_STA&0xC000?1:0; }
uint8_t UART1_Read(uint8_t index){
	if(!UART1_Available()||index>(UART1_ReceivedLength()-1)) return -1;
	return USART1_RX_BUF[index];
}
//uint8_t UART2_Read(uint8_t index){
//	if(!UART2_Available()||index>(UART2_ReceivedLength()-1)) return -1;
//	return USART2_RX_BUF[index];
//}
uint8_t UART6_Read(uint8_t index){
	if(!UART6_Available()||index>(UART6_ReceivedLength()-1)) return -1;
	return USART6_RX_BUF[index];
}
uint8_t* UART1_GetBufferPtr(void) { return (uint8_t *)&USART1_RX_BUF; }
//uint8_t* UART2_GetBufferPtr(void) { return (uint8_t *)&USART2_RX_BUF; }
uint8_t* UART6_GetBufferPtr(void) { return (uint8_t *)&USART6_RX_BUF; }
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	// 所有串口产生的中断都调用这个回调函数, 所以需要判断中断来源.
	// 判断中断来源: 串口 1 (UART1) - USB 转串口
	if(huart==&huart1){
		if(RETURN_ON_RECEIVE) printf("%c", USART1_NewData); // 将收到的数据以符号变量传回上位机, 从而实现边输入边显示 (仅无输出框的终端使用, 如 HyperTerminal)
		if((USART1_RX_STA&0x8000)==0){ // 接收未完成
			if(USART1_RX_STA&0x4000){ // 已经收到 0x0d (代表回车'\r')
				if(USART1_NewData!=0x0a) UART1_Clear(); // 接收错误, 重新开始
				else{
					// 再收到 0x0a (代表换行'\n')
					USART1_RX_STA |= 0x8000; // 接收完成, 加上0x8000标志位
				}
			}
			else{ // 还未收到 0x0d
				if(USART1_NewData==0x0d) USART1_RX_STA |= 0x4000; // 新收到 0x0d, 加上 0x0d 标志位
				else{
					USART1_RX_BUF[USART1_RX_STA&0x3FFF] = USART1_NewData; // 收到的数据放入数组
					USART1_RX_STA++; // 数组长度标志位 +1
					if(USART1_RX_STA>(USART1_REC_LEN-1)) UART1_Clear(); // 超出缓存区容量, 重新开始接收
				}
			}
		}
		UART1_SetCallback();
	}
//	// 判断中断来源: 串口 2 (UART2)
//	else if(huart == &huart2){
//
//	}
	// 判断中断来源: 串口 6 (UART6) - 蓝牙模块
	// 模拟回车换行: 0D0A
	else if(huart == &huart6){
		if((USART6_RX_STA&0x8000)==0){ // 接收未完成
			if(USART6_RX_STA&0x4000){ // 已经收到 ';'
				if(USART6_NewData!='\n') UART6_Clear(); // 接收错误, 重新开始
				else{
					// 再收到 0x0a (代表换行'\n')
					USART6_RX_STA |= 0x8000; // 接收完成, 加上0x8000标志位
				}
//				USART6_RX_STA |= 0x8000; // 接收完成, 加上0x8000标志位
			}
			else{ // 还未收到 0x0d
				if(USART6_NewData==';') USART6_RX_STA |= 0x4000; // 新收到 ';', 加上标志位
				else{
					if(USART6_NewData >= ' ' && USART6_NewData <= 'z'){
						USART6_RX_BUF[USART6_RX_STA&0x3FFF] = USART6_NewData; // 收到的数据放入数组
						USART6_RX_STA++; // 数组长度标志位 +1
						if(USART6_RX_STA>(USART6_REC_LEN-1)) UART6_Clear(); // 超出缓存区容量, 重新开始接收
					}
				}
			}
		}
//		printf("%c", USART6_NewData);
		UART6_SetCallback();
	}
}

#endif
