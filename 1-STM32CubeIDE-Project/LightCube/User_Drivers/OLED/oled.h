/*
 * oled.h
 *
 *  Created on: Nov 2, 2022
 *      Author: Matrix
 */

#ifndef OLED_OLED_H_
#define OLED_OLED_H_

#include "main.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"
#include "../Delay/delay.h"

// 采用软件模拟 I2C
// 下方填入 CubeIDE 中配置的引脚别名
// 使用到 PB3/PB4 引脚，一定要额外关闭 STM32 的调试端口并开启端口复用!
#define OLED_SCL_PORT OLED_SCL_GPIO_Port
#define OLED_SCL_PIN OLED_SCL_Pin

#define OLED_SDA_PORT OLED_SDA_GPIO_Port
#define OLED_SDA_PIN OLED_SDA_Pin

#define OLED_CMD 0  // 写命令
#define OLED_DATA 1 // 写数据
#define USE_I2C 1   // 是否采用 I2C 方式连接

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_PAGE 8

#define BIG_FONT 16
#define SMALL_FONT 12

#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58

extern uint8_t OLED_GRAM[OLED_WIDTH][OLED_PAGE]; // OLED Graphics RAM

void OLED_WriteByte(uint8_t data, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_RefreshGram(void);
void OLED_RefreshGram_Line(uint8_t line);
void OLED_RefreshGram_Pixel(uint8_t x, uint8_t y);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t state);
void OLED_DrawChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_DrawNumber(uint8_t x, uint8_t y, uint32_t num, uint8_t size);
void OLED_DrawString(uint8_t x, uint8_t y, uint8_t size, const char *p);
void OLED_printf(uint8_t x, uint8_t y, uint8_t size, char *fmt, ...);

#endif /* OLED_OLED_H_ */
