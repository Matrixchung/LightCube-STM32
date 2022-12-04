/*
 * bluetooth.h
 *
 *  Created on: Nov 1, 2022
 *      Author: Matrix
 */

#ifndef BLUETOOTH_BLUETOOTH_H_
#define BLUETOOTH_BLUETOOTH_H_

#include "main.h"
#include "../Delay/delay.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"

extern UART_HandleTypeDef huart6; // 蓝牙模块连接在 UART6

void BT_printf(char *fmt, ...);
#define USART_REC_LEN 200

#endif /* BLUETOOTH_BLUETOOTH_H_ */
