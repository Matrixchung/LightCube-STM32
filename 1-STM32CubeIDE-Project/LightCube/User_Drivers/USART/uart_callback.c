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
	// ���д��ڲ������ж϶���������ص�����, ������Ҫ�ж��ж���Դ.
	// �ж��ж���Դ: ���� 1 (UART1) - USB ת����
	if(huart==&huart1){
		if(RETURN_ON_RECEIVE) printf("%c", USART1_NewData); // ���յ��������Է��ű���������λ��, �Ӷ�ʵ�ֱ��������ʾ (�����������ն�ʹ��, �� HyperTerminal)
		if((USART1_RX_STA&0x8000)==0){ // ����δ���
			if(USART1_RX_STA&0x4000){ // �Ѿ��յ� 0x0d (����س�'\r')
				if(USART1_NewData!=0x0a) UART1_Clear(); // ���մ���, ���¿�ʼ
				else{
					// ���յ� 0x0a (������'\n')
					USART1_RX_STA |= 0x8000; // �������, ����0x8000��־λ
				}
			}
			else{ // ��δ�յ� 0x0d
				if(USART1_NewData==0x0d) USART1_RX_STA |= 0x4000; // ���յ� 0x0d, ���� 0x0d ��־λ
				else{
					USART1_RX_BUF[USART1_RX_STA&0x3FFF] = USART1_NewData; // �յ������ݷ�������
					USART1_RX_STA++; // ���鳤�ȱ�־λ +1
					if(USART1_RX_STA>(USART1_REC_LEN-1)) UART1_Clear(); // ��������������, ���¿�ʼ����
				}
			}
		}
		UART1_SetCallback();
	}
//	// �ж��ж���Դ: ���� 2 (UART2)
//	else if(huart == &huart2){
//
//	}
	// �ж��ж���Դ: ���� 6 (UART6) - ����ģ��
	// ģ��س�����: 0D0A
	else if(huart == &huart6){
		if((USART6_RX_STA&0x8000)==0){ // ����δ���
			if(USART6_RX_STA&0x4000){ // �Ѿ��յ� ';'
				if(USART6_NewData!='\n') UART6_Clear(); // ���մ���, ���¿�ʼ
				else{
					// ���յ� 0x0a (������'\n')
					USART6_RX_STA |= 0x8000; // �������, ����0x8000��־λ
				}
//				USART6_RX_STA |= 0x8000; // �������, ����0x8000��־λ
			}
			else{ // ��δ�յ� 0x0d
				if(USART6_NewData==';') USART6_RX_STA |= 0x4000; // ���յ� ';', ���ϱ�־λ
				else{
					if(USART6_NewData >= ' ' && USART6_NewData <= 'z'){
						USART6_RX_BUF[USART6_RX_STA&0x3FFF] = USART6_NewData; // �յ������ݷ�������
						USART6_RX_STA++; // ���鳤�ȱ�־λ +1
						if(USART6_RX_STA>(USART6_REC_LEN-1)) UART6_Clear(); // ��������������, ���¿�ʼ����
					}
				}
			}
		}
//		printf("%c", USART6_NewData);
		UART6_SetCallback();
	}
}

#endif
