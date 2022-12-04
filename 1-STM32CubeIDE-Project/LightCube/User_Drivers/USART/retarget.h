/*
 * retarget.h
 * Note: you need to EXCLUDE Core/Src/syscall.c first !!!
 */

#ifndef USART_RETARGET_H_
#define USART_RETARGET_H_

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include <sys/stat.h>

void UART_RetargetInit(UART_HandleTypeDef *huart);

int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);


#endif /* USART_RETARGET_H_ */
