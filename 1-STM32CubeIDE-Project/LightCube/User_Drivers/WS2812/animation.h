/*
 * animation.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Matrix
 */

#ifndef WS2812_ANIMATION_H_
#define WS2812_ANIMATION_H_

#include "ws2812.h"
#include "../Utils/utils.h"

#define COLOR_BLACK 0, 0, 0
#define COLOR_WHITE 255, 255, 255
#define COLOR_RED 255, 0, 0
#define COLOR_GREEN 0, 255, 0
#define COLOR_BLUE 0, 0, 255
#define COLOR_YELLOW 255, 255, 0
#define COLOR_CYAN 0, 255, 255
#define COLOR_PURPLE 128, 0, 255
#define COLOR_ORANGE 255, 128, 0

extern float LED_BRIGHTNESS;
extern const uint8_t gradientR[360];
extern const uint8_t gradientG[360];
extern const uint8_t gradientB[360];

void LED_BreatheOnePixel(uint8_t x, uint8_t y, uint8_t z, uint16_t hue, uint16_t sat, uint16_t times);
void LED_BreatheBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint16_t hue, uint16_t sat, uint16_t times);
void LED_GradientOnePixel(uint8_t x, uint8_t y, uint8_t z);
void LED_GradientBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2);
void LED_Anim_GradientLayer(uint8_t times);
void LED_Anim_FlashLayer(uint8_t times);
void LED_Anim_Heart(uint8_t times);
void LED_Anim_Rain(uint8_t times);
void LED_Anim_CycleOnOff(uint8_t times);
void LED_Anim_RainbowWave(uint8_t times);
void LED_Anim_Countdown(uint8_t times);
void LED_Anim_Snake(uint8_t times);
void LED_Anim_ShowNumber(uint8_t num, uint8_t face, uint8_t layer, uint8_t r, uint8_t g, uint8_t b);

#endif /* WS2812_ANIMATION_H_ */
