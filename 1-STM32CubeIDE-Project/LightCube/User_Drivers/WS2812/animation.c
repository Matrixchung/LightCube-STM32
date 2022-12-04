/*
 * animation.c
 *
 *  Created on: Dec 1, 2022
 *      Author: Matrix
 */
#include "animation.h"
const uint8_t gradientR[360] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,250,246,242,237,233,229,225,221,216,212,208,203,199,195,191,187,182,178,174,169,165,161,157,153,148,144,140,135,131,127,123,119,114,110,106,101,97,93,89,85,80,76,72,67,63,59,55,51,46,42,38,33,29,25,21,17,12,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,21,25,29,33,38,42,46,50,55,59,63,68,72,76,80,85,89,93,97,102,106,110,114,119,123,127,131,135,140,144,148,152,157,161,165,169,174,178,182,186,191,195,199,204,208,212,216,221,225,229,233,238,242,246,250,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
const uint8_t gradientG[360] = {0,4,8,12,16,21,25,29,33,38,42,46,50,55,59,63,67,72,76,80,85,89,93,97,101,106,110,114,119,123,127,131,136,140,144,148,153,157,161,165,170,174,178,182,187,191,195,199,204,208,212,216,221,225,229,233,238,242,246,250,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,250,246,242,238,233,229,225,220,216,212,208,203,199,195,191,187,182,178,174,170,165,161,157,152,148,144,140,135,131,127,123,119,114,110,106,102,97,93,89,84,80,76,72,67,63,59,55,51,46,42,38,34,29,25,21,16,12,8,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint8_t gradientB[360] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,21,25,29,34,38,42,46,51,55,59,63,67,72,76,80,84,89,93,97,102,106,110,114,119,123,127,131,135,140,144,148,152,157,161,165,170,174,178,182,187,191,195,199,203,208,212,216,220,225,229,233,238,242,246,250,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,250,246,242,238,233,229,225,221,216,212,208,204,199,195,191,186,182,178,174,169,165,161,157,152,148,144,140,135,131,127,123,119,114,110,106,102,97,93,89,85,80,76,72,68,63,59,55,50,46,42,38,33,29,25,21,16,12,8,4};

void LED_BreatheOnePixel(uint8_t x, uint8_t y, uint8_t z, uint16_t hue, uint16_t sat, uint16_t times){
	uint8_t r, g, b;
	for(;times>0;times--){
		for(uint8_t i = 1; i<=10; i++){
			hsv_to_rgb(hue, sat, i*10, &r, &g, &b);
			LED_SetColor(x,y,z,r,g,b);
			LED_Update();
			HAL_Delay(60);
		}
		for(uint8_t i = 10; i>=1; i--){
			hsv_to_rgb(hue, sat, i*10, &r, &g, &b);
			LED_SetColor(x,y,z,r,g,b);
			LED_Update();
			HAL_Delay(60);
		}
		LED_SetColor(x,y,z,0,0,0);
		LED_Update();
		HAL_Delay(120);
	}
//	LED_ResetAll();
	LED_SetColor(x,y,z,0,0,0);
	LED_Update();
}
void LED_BreatheBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, uint16_t hue, uint16_t sat, uint16_t times){
	if(x1>x2) swap_u8(&x1, &x2);
	if(y1>y2) swap_u8(&y1, &y2);
	if(z1>z2) swap_u8(&z1, &z2);
	uint8_t r, g, b;
	for(;times>0;times--){
		for(uint8_t i = 1; i<=10; i++){
			hsv_to_rgb(hue, sat, i*10, &r, &g, &b);
			for(uint8_t x = x1;x<=x2;x++){
				for(uint8_t y = y1;y<=y2;y++){
					for(uint8_t z = z1;z<=z2;z++) LED_SetColor(x,y,z,r,g,b);
				}
			}
			LED_Update();
			HAL_Delay(60);
		}
		for(uint8_t i = 10; i>=1; i--){
			hsv_to_rgb(hue, sat, i*10, &r, &g, &b);
			for(uint8_t x = x1;x<=x2;x++){
				for(uint8_t y = y1;y<=y2;y++){
					for(uint8_t z = z1;z<=z2;z++) LED_SetColor(x,y,z,r,g,b);
				}
			}
			LED_Update();
			HAL_Delay(60);
		}
		LED_ResetAll();
		LED_Update();
		HAL_Delay(120);
	}
	LED_ResetAll();
	LED_Update();
}
void LED_GradientOnePixel(uint8_t x, uint8_t y, uint8_t z){
//	uint8_t r, g, b;
	for(uint16_t i = 0; i<=359; i++){
//		hsv_to_rgb(i, 100, 100, &r, &g, &b);
		LED_SetColor(x,y,z,gradientR[i],gradientG[i],gradientB[i]);
		LED_Update();
		HAL_Delay(15);
	}
	LED_SetColor(x,y,z,0,0,0);
	LED_Update();
}
void LED_GradientBatch(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2){
	if(x1>x2) swap_u8(&x1, &x2);
	if(y1>y2) swap_u8(&y1, &y2);
	if(z1>z2) swap_u8(&z1, &z2);
	for(uint16_t i = 0; i<=359; i++){
//		hsv_to_rgb(i, 100, 100, &r, &g, &b);
//		LED_SetColor(x,y,z,r,g,b);
		for(uint8_t x = x1;x<=x2;x++){
			for(uint8_t y = y1;y<=y2;y++){
				for(uint8_t z = z1;z<=z2;z++) LED_SetColor(x,y,z,gradientR[i],gradientG[i],gradientB[i]);
			}
		}
		LED_Update();
		HAL_Delay(15);
	}
	LED_ResetAll();
	LED_Update();
}
void LED_Anim_GradientLayer(uint8_t times){
	for(;times>0;times--){
		for(uint16_t i = 5; i <= 71; i++){
			for(uint8_t x = 1;x <= 5;x++){
				for(uint8_t y = 1;y <= 5;y++){
					LED_SetColor(x,y,5,gradientR[i-y],gradientG[i-y],gradientB[i-y]);
				}
			}
			LED_Update();
			HAL_Delay(15);
		}
		LED_ResetXY(5);
		LED_Update();
		for(uint16_t i = 77; i <= 143; i++){
			for(uint8_t x = 1;x<=5;x++){
				for(uint8_t y = 1;y<=5;y++){
					LED_SetColor(x,y,4,gradientR[i-y],gradientG[i-y],gradientB[i-y]);
				}
			}
			LED_Update();
			HAL_Delay(15);
		}
		LED_ResetXY(4);
		LED_Update();
		for(uint16_t i = 148; i <= 214; i++){
			for(uint8_t x = 1;x<=5;x++){
				for(uint8_t y = 1;y<=5;y++){
					LED_SetColor(x,y,3,gradientR[i-y],gradientG[i-y],gradientB[i-y]);
				}
			}
			LED_Update();
			HAL_Delay(15);
		}
		LED_ResetXY(3);
		LED_Update();
		for(uint16_t i = 219; i <= 285; i++){
			for(uint8_t x = 1;x<=5;x++){
				for(uint8_t y = 1;y<=5;y++){
					LED_SetColor(x,y,2,gradientR[i-y],gradientG[i-y],gradientB[i-y]);
				}
			}
			LED_Update();
			HAL_Delay(15);
		}
		LED_ResetXY(2);
		LED_Update();
		for(uint16_t i = 290; i <= 359; i++){
			for(uint8_t x = 1;x<=5;x++){
				for(uint8_t y = 1;y<=5;y++){
					LED_SetColor(x,y,1,gradientR[i-y],gradientG[i-y],gradientB[i-y]);
				}
			}
			LED_Update();
			HAL_Delay(15);
		}
		LED_ResetXY(1);
		LED_Update();
	}
}
void LED_Anim_FlashLayer(uint8_t times){
	for(;times>0;times--){
		// Z-Up
		for(uint8_t z = 1; z <= 5; z++){
			for(uint8_t x = 1; x <= 5; x++){
				for(uint8_t y = 1; y <= 5; y++){
					LED_SetColor(x,y,z,COLOR_GREEN);
				}
			}
			LED_Update();
			HAL_Delay(100);
			LED_ResetXY(z);
		}
		// X-Right
		for(uint8_t x = 1; x <= 5; x++){
			for(uint8_t y = 1; y <= 5; y++){
				for(uint8_t z = 1; z <= 5; z++){
					LED_SetColor(x,y,z,COLOR_YELLOW);
				}
			}
			LED_Update();
			HAL_Delay(100);
			LED_ResetYZ(x);
		}
		// Y-Front
		for(uint8_t y = 1; y <= 5; y++){
			for(uint8_t x = 1; x <= 5; x++){
				for(uint8_t z = 1; z <= 5; z++){
					LED_SetColor(x,y,z,COLOR_BLUE);
				}
			}
			LED_Update();
			HAL_Delay(100);
			LED_ResetXZ(y);
		}
	}
}
void LED_Anim_Heart(uint8_t times){
	for(;times>0;times--){
		for(uint8_t i = 1; i <= 5; i++){
			LED_ResetAll();
			LED_DrawBitmap(10, 2, 6-i, COLOR_RED);
			for(uint8_t z = 1; z <= 5; z++){
				LED_SetColor(1, 1, z, gradientR[i*40+z*30], gradientG[i*40+z*30], gradientB[i*40+z*30]);
				LED_SetColor(5, 1, z, gradientR[i*40+z*30], gradientG[i*40+z*30], gradientB[i*40+z*30]);
				LED_SetColor(5, 5, z, gradientR[i*40+z*30], gradientG[i*40+z*30], gradientB[i*40+z*30]);
				LED_SetColor(1, 5, z, gradientR[i*40+z*30], gradientG[i*40+z*30], gradientB[i*40+z*30]);
			}
			LED_Update();
			HAL_Delay(100);
		}
	}
}
void LED_Anim_Rain(uint8_t times){
	for(;times>0;times--){
		uint8_t waterLayer = 0;
		for(uint8_t i = 1; i <= 10; i++){
			for(uint8_t j = 5; j >= waterLayer + 1; j--){
				LED_ResetAll();
				LED_DrawBitmap(i%2?12:11, 2, j, COLOR_BLUE);
				LED_SetColorBatch(1, 1, 1, 5, 5, waterLayer, COLOR_BLUE);
				LED_Update();
				HAL_Delay(600);
			}
			if(i%3==0&&waterLayer<2) waterLayer++;
		}
	}
}
void LED_Anim_CycleOnOff(uint8_t times){
	for(;times>0;times--){
		LED_SetColorAll(120*LED_BRIGHTNESS, 120*LED_BRIGHTNESS, 120*LED_BRIGHTNESS);
		LED_Update();
		HAL_Delay(500);
		LED_ResetAll();
		LED_Update();
		HAL_Delay(500);
	}
}
void LED_Anim_RainbowWave(uint8_t times){
	for(;times>0;times--){
		for(uint8_t j = 0; j < 5; j++){
			for(uint16_t i = 0, firstZ = 1; i <= 359; i++){
				LED_ResetAll();
				firstZ = i/72 + 1;
				for(uint8_t j = 1; j <= firstZ; j++) LED_SetColorBatch(j, 1, firstZ-j+1, j, 5, firstZ-j+1, gradientR[i], gradientG[i], gradientB[i]);
				LED_Update();
//				HAL_Delay(1);
			}
			for(uint16_t i = 359, highestX = 1; i >= 1; i--){
				LED_ResetAll();
				highestX = 5 - i/72;
				for(uint8_t x = 1; x <= highestX; x++) LED_SetColorBatch(x, 1, 5-highestX+x, x, 5, 5-highestX+x, gradientR[i], gradientG[i], gradientB[i]);
				for(uint8_t x = highestX+1; x <= 5; x++) LED_SetColorBatch(x, 1, 5+highestX-x, x, 5, 5+highestX-x, gradientR[i], gradientG[i], gradientB[i]);
				LED_Update();
//				HAL_Delay(1);
			}
		}
		LED_ResetAll();
		LED_Update();
	}
}
void LED_Anim_Snake(uint8_t times){
	LED_ResetAll();
	for(;times>0;times--){
		for(uint8_t i = 1; i <= 5; i++){
			LED_SetColor(i, 1, 1, gradientR[i*20], gradientG[i*20], gradientB[i*20]);
			LED_SetColor(6-i, 5, 1, gradientR[i*20], gradientG[i*20], gradientB[i*20]);
			LED_Update();
			HAL_Delay(100);
		}
		for(uint8_t i = 2; i <= 5; i++){
			LED_SetColor(5, 1, i, gradientR[100+i*20], gradientG[100+i*20], gradientB[100+i*20]);
			LED_SetColor(1, 5, i, gradientR[100+i*20], gradientG[100+i*20], gradientB[100+i*20]);
			LED_Update();
			HAL_Delay(100);
		}
		for(uint8_t i = 4; i >= 2; i--){
			LED_SetColor(i, 1, 5, gradientR[200+(7-i)*20], gradientG[200+(7-i)*20], gradientB[200+(7-i)*20]);
			LED_SetColor(6-i, 5, 5, gradientR[200+(7-i)*20], gradientG[200+(7-i)*20], gradientB[200+(7-i)*20]);
			LED_Update();
			HAL_Delay(100);
		}
		LED_SetColor(2, 2, 5, gradientR[310], gradientG[310], gradientB[310]);
		LED_SetColor(4, 4, 5, gradientR[310], gradientG[310], gradientB[310]);
		LED_Update();
		HAL_Delay(100);
		for(uint8_t i = 4; i >= 2; i--){
			LED_SetColor(2, 2, i, gradientR[(7-i)*20], gradientG[(7-i)*20], gradientB[(7-i)*20]);
			LED_SetColor(4, 4, i, gradientR[(7-i)*20], gradientG[(7-i)*20], gradientB[(7-i)*20]);
			LED_Update();
			HAL_Delay(100);
		}
		for(uint8_t i = 2; i<= 4; i++){
			LED_SetColor(i, 2, 2, gradientR[100+i*20], gradientG[100+i*20], gradientB[100+i*20]);
			LED_SetColor(6-i, 4, 2, gradientR[100+i*20], gradientG[100+i*20], gradientB[100+i*20]);
			LED_Update();
			HAL_Delay(100);
		}
		LED_SetColor(4, 2, 3, gradientR[210], gradientG[210], gradientB[210]);
		LED_SetColor(2, 4, 3, gradientR[210], gradientG[210], gradientB[210]);
		LED_Update();
		HAL_Delay(100);
		LED_SetColor(4, 3, 3, gradientR[240], gradientG[240], gradientB[240]);
		LED_SetColor(2, 3, 3, gradientR[240], gradientG[240], gradientB[240]);
		LED_Update();
		HAL_Delay(100);
		LED_SetColor(3, 3, 3, gradientR[260], gradientG[260], gradientB[260]);
		LED_Update();
		HAL_Delay(100);
		LED_ResetAll();
		LED_Update();
	}
}
void LED_Anim_RainbowSpin(uint8_t times){
	for(;times>0;times--){

	}
}
// up: red -> yellow -> orange -> blue -> green
const uint8_t waveIndex[10] =    {1, 2, 3, 4, 5, 2, 4, 1, 3, 5};
const uint8_t waveStrength[10] = {3, 1, 4, 2, 5, 1, 2, 3, 5, 1};
void LED_Anim_MusicWave(uint8_t times){
	for(;times>0;times--){
		LED_ResetAll();
	}
}
void LED_Anim_Countdown(uint8_t times){
	for(;times>0;times--){
		for(uint8_t i = 10; i>=1; i--){
			for(uint8_t j = 5; j >= 1; j--){
				LED_ResetAll();
				LED_DrawBitmap(i-1, 2, j, COLOR_BLUE);
				LED_SetColorBatch(1, 1, 1, 1, 1, 5, COLOR_BLUE);
				LED_SetColorBatch(5, 1, 1, 5, 1, 5, COLOR_BLUE);
				LED_SetColorBatch(1, 5, 1, 1, 5, 5, COLOR_BLUE);
				LED_SetColorBatch(5, 5, 1, 5, 5, 5, COLOR_BLUE);
				LED_Update();
				HAL_Delay(200);
			}
		}
		LED_ResetAll();
		LED_Update();
	}
}
// face: 1 - XoZ 2 - XoY 3 - YoZ
// layer: [1, 5]
void LED_Anim_ShowNumber(uint8_t num, uint8_t face, uint8_t layer, uint8_t r, uint8_t g, uint8_t b){
	if(num<0||num>9) return;
	LED_DrawBitmap(num, face, layer, r, g, b);
	LED_Update();
}
