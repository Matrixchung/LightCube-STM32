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

// �������ģ�� I2C
// �·����� CubeIDE �����õ����ű���
// ʹ�õ� PB3/PB4 ���ţ�һ��Ҫ����ر� STM32 �ĵ��Զ˿ڲ������˿ڸ���!
#define OLED_SCL_PORT OLED_SCL_GPIO_Port
#define OLED_SCL_PIN OLED_SCL_Pin

#define OLED_SDA_PORT OLED_SDA_GPIO_Port
#define OLED_SDA_PIN OLED_SDA_Pin

#define OLED_CMD 0  // д����
#define OLED_DATA 1 // д����
#define USE_I2C 1   // �Ƿ���� I2C ��ʽ����

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
