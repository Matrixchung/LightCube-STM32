/*
 * ws2812.c
 *
 *  Created on: Nov 25, 2022
 *      Author: Matrix
 */
#include "ws2812.h"
#include "images.h"

float LED_BRIGHTNESS = DEFAULT_BRIGHTNESS;
uint8_t dma_flag = 0;
uint8_t COLOR_PLANE1[LEDS_PER_PLANE][3]; // [index][r, g, b]
uint8_t COLOR_PLANE2[LEDS_PER_PLANE][3]; // [index][r, g, b]
uint8_t COLOR_PLANE3[LEDS_PER_PLANE][3]; // [index][r, g, b]
uint8_t COLOR_PLANE4[LEDS_PER_PLANE][3]; // [index][r, g, b]
uint8_t COLOR_PLANE5[LEDS_PER_PLANE][3]; // [index][r, g, b]
uint32_t DMA_BUF_TIM2_CH3[DMA_BUF_LEN];
uint32_t DMA_BUF_TIM3_CH1[DMA_BUF_LEN];
uint32_t DMA_BUF_TIM3_CH2[DMA_BUF_LEN];
uint32_t DMA_BUF_TIM3_CH3[DMA_BUF_LEN];
uint32_t DMA_BUF_TIM3_CH4[DMA_BUF_LEN];
// index: [0, NUM_LEDS-1]
void _setDmaBuf32(uint32_t* data, uint8_t index, uint8_t r, uint8_t g, uint8_t b){
	for(uint8_t i = 0; i < 8; i++){
		// R-G-B Seq. 8 Bits / Byte
		*(data+24*index+i+DMA_BUF_OFFSET_HEAD) = (r & (0x80 >> i)) ? BIT1:BIT0;
		*(data+24*index+i+8+DMA_BUF_OFFSET_HEAD) = (g & (0x80 >> i)) ? BIT1:BIT0;
		*(data+24*index+i+16+DMA_BUF_OFFSET_HEAD) = (b & (0x80 >> i)) ? BIT1:BIT0;
	}
}
void LED_Update(void){
//	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_3);
	for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
		_setDmaBuf32(DMA_BUF_TIM3_CH1, i, COLOR_PLANE3[i][0], COLOR_PLANE3[i][1], COLOR_PLANE3[i][2]);
	}
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, DMA_BUF_TIM3_CH1, DMA_BUF_LEN);
//	while(!dma_flag);
//	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
//	dma_flag = 0;

	for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
		_setDmaBuf32(DMA_BUF_TIM3_CH2, i, COLOR_PLANE2[i][0], COLOR_PLANE2[i][1], COLOR_PLANE2[i][2]);
	}
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, DMA_BUF_TIM3_CH2, DMA_BUF_LEN);
//	while(!dma_flag);
//	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_2);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);
//	dma_flag = 0;

	for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
		_setDmaBuf32(DMA_BUF_TIM3_CH3, i, COLOR_PLANE1[i][0], COLOR_PLANE1[i][1], COLOR_PLANE1[i][2]);
	}
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, DMA_BUF_TIM3_CH3, DMA_BUF_LEN);
//	while(!dma_flag);
//	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_3);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,0);
//	dma_flag = 0;

	for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
		_setDmaBuf32(DMA_BUF_TIM2_CH3, i, COLOR_PLANE4[i][0], COLOR_PLANE4[i][1], COLOR_PLANE4[i][2]);
	}
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, DMA_BUF_TIM2_CH3, DMA_BUF_LEN);
//	while(!dma_flag);
//	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_3);
//	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);
//	dma_flag = 0;

	for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
		_setDmaBuf32(DMA_BUF_TIM3_CH4, i, COLOR_PLANE5[i][0], COLOR_PLANE5[i][1], COLOR_PLANE5[i][2]);
	}
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_4, (uint32_t *)DMA_BUF_TIM3_CH4, DMA_BUF_LEN);
//	while(!dma_flag);
//	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_4);
//	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,0);
//	dma_flag = 0;
}
void LED_UpdatePlane(uint8_t x){
	switch(x){
	case 1:
		for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
			_setDmaBuf32(DMA_BUF_TIM3_CH3, i, COLOR_PLANE1[i][0], COLOR_PLANE1[i][1], COLOR_PLANE1[i][2]);
		}
		HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_3, DMA_BUF_TIM3_CH3, DMA_BUF_LEN);
		return;
	case 2:
		for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
			_setDmaBuf32(DMA_BUF_TIM3_CH2, i, COLOR_PLANE2[i][0], COLOR_PLANE2[i][1], COLOR_PLANE2[i][2]);
		}
		HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, DMA_BUF_TIM3_CH2, DMA_BUF_LEN);
		return;
	case 3:
		for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
			_setDmaBuf32(DMA_BUF_TIM3_CH1, i, COLOR_PLANE3[i][0], COLOR_PLANE3[i][1], COLOR_PLANE3[i][2]);
		}
		HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, DMA_BUF_TIM3_CH1, DMA_BUF_LEN);
		return;
	case 4:
		for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
			_setDmaBuf32(DMA_BUF_TIM2_CH3, i, COLOR_PLANE4[i][0], COLOR_PLANE4[i][1], COLOR_PLANE4[i][2]);
		}
		HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, DMA_BUF_TIM2_CH3, DMA_BUF_LEN);
		return;
	case 5:
		for(uint8_t i = 0; i < LEDS_PER_PLANE; i++){
			_setDmaBuf32(DMA_BUF_TIM3_CH4, i, COLOR_PLANE5[i][0], COLOR_PLANE5[i][1], COLOR_PLANE5[i][2]);
		}
		HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_4, (uint32_t *)DMA_BUF_TIM3_CH4, DMA_BUF_LEN);
		return;
	default: return;
	}
}
// index: [0, NUM_LEDS-1]
// x: [1, 5]
// y: [1, 5]
// z: [1, 5]
// Based on left-front corner('30' mark on pcb)
// first vertical plane: PB0 -> TIM3_CH3
// second: PA7 -> TIM3_CH2
// third: PA6 -> TIM3_CH1
// fourth: PB10 -> TIM2_CH3
// fifth: PB1 -> TIM3_CH4
void LED_SetColor(uint8_t x, uint8_t y, uint8_t z, uint8_t r, uint8_t g, uint8_t b){
	if(x<1||y<1||z<1||x>5||y>5||z>5) return;
	uint8_t index = 0;
	switch(z){
	case 1:
		index = y - 1;
		break;
	case 2:
		index = 10 - y;
		break;
	case 3:
		index = y + 9;
		break;
	case 4:
		index = 20 - y;
		break;
	case 5:
		index = y + 19;
		break;
	}
	switch(x){
	case 1: // first plane
		//_setDmaBuf32(DMA_BUF_TIM3_CH3, index, r, g, b);
		COLOR_PLANE1[index][0] = r;
		COLOR_PLANE1[index][1] = g;
		COLOR_PLANE1[index][2] = b;
		return;
	case 2: // second
//		_setDmaBuf32(DMA_BUF_TIM3_CH2, index, r, g, b);
		COLOR_PLANE2[index][0] = r;
		COLOR_PLANE2[index][1] = g;
		COLOR_PLANE2[index][2] = b;
		return;
	case 3: // third
//		_setDmaBuf32(DMA_BUF_TIM3_CH1, index, r, g, b);
		COLOR_PLANE3[index][0] = r;
		COLOR_PLANE3[index][1] = g;
		COLOR_PLANE3[index][2] = b;
		return;
	case 4:
//		_setDmaBuf32(DMA_BUF_TIM2_CH3, index, r, g, b);
		COLOR_PLANE4[index][0] = r;
		COLOR_PLANE4[index][1] = g;
		COLOR_PLANE4[index][2] = b;
		return;
	case 5:
//		_setDmaBuf32(DMA_BUF_TIM3_CH4, index, r, g, b);
		COLOR_PLANE5[index][0] = r;
		COLOR_PLANE5[index][1] = g;
		COLOR_PLANE5[index][2] = b;
		return;
	}
}
// Reset YoZ Plane
void LED_ResetYZ(uint8_t x){
	switch(x){
	case 1:
		memset(COLOR_PLANE1, 0, LEDS_PER_PLANE*3);
		return;
	case 2:
		memset(COLOR_PLANE2, 0, LEDS_PER_PLANE*3);
		return;
	case 3:
		memset(COLOR_PLANE3, 0, LEDS_PER_PLANE*3);
		return;
	case 4:
		memset(COLOR_PLANE4, 0, LEDS_PER_PLANE*3);
		return;
	case 5:
		memset(COLOR_PLANE5, 0, LEDS_PER_PLANE*3);
		return;
	}
}
void LED_DrawBitmap(uint8_t index, uint8_t face, uint8_t layer, uint8_t r, uint8_t g, uint8_t b){
	if(face<1||face>3||layer<1||layer>5||index<0||index>=IMAGES_COUNT) return;
	switch(face){
	case 1: // XoZ
		LED_ResetXZ(layer);
		for(uint8_t z = 5; z >= 1; z--){
			for(uint8_t x = 1; x <= 5; x++){
				if(images[index][24+x-5*z]) LED_SetColor(x, layer, z, r, g, b);
			}
		}
		break;
	case 2: // XoY
		LED_ResetXY(layer);
		for(uint8_t y = 5; y >= 1; y--){
			for(uint8_t x = 1; x <= 5; x++){
				if(images[index][24+x-5*y]) LED_SetColor(x, y, layer, r, g, b);
			}
		}
		break;
	case 3: // YoZ
		LED_ResetYZ(layer);
		for(uint8_t z = 5; z >= 1; z--){
			for(uint8_t y = 1; y <= 5; y++){
				if(images[index][24+y-5*z]) LED_SetColor(layer, y, z, r, g, b);
			}
		}
		break;
	default: break;
	}
}
void LED_SetColorBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint8_t r, uint8_t g, uint8_t b){
	for(uint8_t x = x1;x<=x2;x++){
		for(uint8_t y = y1;y<=y2;y++){
			for(uint8_t z = z1;z<=z2;z++) LED_SetColor(x,y,z,r,g,b);
		}
	}
}
// Reset XoZ Plane
void LED_ResetXZ(uint8_t y){
	for(uint8_t x = 1; x <= LED_WIDTH; x++){
		for(uint8_t z = 1; z <= LED_WIDTH; z++){
			LED_SetColor(x,y,z,0,0,0);
		}
	}
}
// Reset XoY Plane
void LED_ResetXY(uint8_t z){
	for(uint8_t x = 1; x <= LED_WIDTH; x++){
		for(uint8_t y = 1; y <= LED_WIDTH; y++){
			LED_SetColor(x,y,z,0,0,0);
		}
	}
}
void LED_SetBrightness(uint8_t brightness){
	if(brightness>100||brightness<0) return;
	LED_BRIGHTNESS = brightness/100.0;
}
void LED_ResetAll(void){
	memset(COLOR_PLANE1, 0, LEDS_PER_PLANE*3);
	memset(COLOR_PLANE2, 0, LEDS_PER_PLANE*3);
	memset(COLOR_PLANE3, 0, LEDS_PER_PLANE*3);
	memset(COLOR_PLANE4, 0, LEDS_PER_PLANE*3);
	memset(COLOR_PLANE5, 0, LEDS_PER_PLANE*3);
}
void LED_SetColorAll(uint8_t r, uint8_t g, uint8_t b){
	for(uint8_t x = 1; x <= LED_WIDTH; x++){
		for(uint8_t y = 1; y <= LED_WIDTH; y++){
			for(uint8_t z = 1; z <= LED_WIDTH; z++){
				LED_SetColor(x,y,z,r,g,b);
			}
		}
	}
}
//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
//{
//	dma_flag = 1;
//}
