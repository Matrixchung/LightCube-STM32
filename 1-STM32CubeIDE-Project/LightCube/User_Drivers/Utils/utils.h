/*
 * utils.h
 *
 *  Created on: Oct 26, 2022
 *      Author: Matrix
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "main.h"
#include "stdlib.h"

void splitData(uint8_t* pSource, uint8_t Lsource, uint16_t* pDest, uint8_t* Ldest, uint8_t split);
void rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b, uint16_t *h, uint16_t *s, uint16_t *v);
void hsv_to_rgb(uint16_t h, uint16_t s, uint16_t v, uint8_t *r, uint8_t *g, uint8_t *b);
void getRGBWithBrightness(uint8_t r, uint8_t g, uint8_t b, uint8_t bright, uint8_t *resR, uint8_t *resG, uint8_t *resB);
void swap_u8(uint8_t *a, uint8_t *b);
void swap_u16(uint16_t *a, uint16_t *b);
uint8_t getRandomNumber(uint8_t start, uint8_t end, uint8_t seedModifier);
#endif /* UTILS_UTILS_H_ */
