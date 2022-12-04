/*
 * ws2812.h
 *
 *  Created on: Nov 25, 2022
 *      Author: Matrix
 */

#ifndef WS2812_WS2812_H_
#define WS2812_WS2812_H_

#include "main.h"
#include "string.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// ~588KHz PWM Wave with 169(+1) counter period
#define BIT1 90 // BIT1/170 * 1/588KHz = 1360 ns
#define BIT0 35 // BIT0/170 * 1/588KHz = 350 ns

#define LED_WIDTH 5
#define LEDS_PER_PLANE (LED_WIDTH)*(LED_WIDTH) // 5x5x5
#define DMA_BUF_OFFSET_HEAD 30
#define DMA_BUF_LEN 2*DMA_BUF_OFFSET_HEAD+(LEDS_PER_PLANE)*24+1
#define DEFAULT_BRIGHTNESS 1 // Default Brightness [0, 1]

//extern uint32_t COLOR_DATA_TIM2_CH3[24*NUM_LEDS+1];
//extern uint32_t COLOR_DATA_TIM3_CH1[24*NUM_LEDS+1];
//extern uint32_t COLOR_DATA_TIM3_CH2[24*NUM_LEDS+1];
//extern uint32_t COLOR_DATA_TIM3_CH3[24*NUM_LEDS+1];
//extern uint32_t COLOR_DATA_TIM3_CH4[24*NUM_LEDS+1];

void LED_Update(void);
void LED_UpdatePlane(uint8_t x);
void LED_ResetYZ(uint8_t x);
void LED_ResetXZ(uint8_t y);
void LED_ResetXY(uint8_t z);
void LED_ResetAll(void);
void LED_SetColor(uint8_t x, uint8_t y, uint8_t z, uint8_t r, uint8_t g, uint8_t b);
void LED_SetColorBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint8_t r, uint8_t g, uint8_t b);
void LED_SetColorAll(uint8_t r, uint8_t g, uint8_t b);
void LED_SetBrightness(uint8_t brightness);
void LED_DrawBitmap(uint8_t index, uint8_t face, uint8_t layer, uint8_t r, uint8_t g, uint8_t b);

#endif /* WS2812_WS2812_H_ */
