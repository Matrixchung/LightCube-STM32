/*
 * utils.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Matrix
 */
#include "utils.h"

// length of pDest must be bigger than Lsource!
void splitData(uint8_t* pSource, uint8_t Lsource, uint16_t* pDest, uint8_t* Ldest, uint8_t split) {
    uint8_t temp = 0;
    *Ldest = 0;
    for (uint8_t i = 0; i < Lsource; i++) *(pDest+i) = 0; // flush the dest buffer
    for (uint8_t i = 0; i < Lsource && *Ldest < Lsource ; i++) {
        temp = *(pSource + i);
        if (temp != split) {
            if (temp >= '0' && temp <= '9') { // is number
                *(pDest + *(Ldest)) *= 10;
                *(pDest + *(Ldest)) += temp - '0';
                if (i == Lsource - 1 || (*(pDest + *(Ldest)) == 0 && temp == '0')) *(Ldest) += 1; // last number
            }
        }
        else if (*(pDest + *(Ldest)) != 0) *(Ldest) += 1;
    }
}
// r g b: [0, 255]
void rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b, uint16_t *h, uint16_t *s, uint16_t *v){
	float R = r/255.0;
	float G = g/255.0;
	float B = b/255.0;
	float max = R>G?(R>B?R:B):(G>B?G:B);
	float min = R<G?(R<B?R:B):(G<B?G:B);
	float delta = max - min;
	if(delta==0) *h = 0;
	else if(max==R) *h = 60.0*(((uint16_t)((G-B)/delta))%6);
	else if(max==G) *h = 60.0*((B-R)/delta+2);
	else if(max==B) *h = 60.0*((R-G)/delta+4);
	*s = max==0?0:(uint16_t)(100*delta/max);
	*v = (uint16_t)(100*max);
}
// h: [0, 359] s: [0, 100] v: [0, 100]
void hsv_to_rgb(uint16_t h, uint16_t s, uint16_t v, uint8_t *r, uint8_t *g, uint8_t *b)
{
	if(h<0||h>359||s<0||s>100||v<0||v>100){
		*r = *g = *b = 0;
		return;
	}
    float C = 0,X = 0,Y = 0,Z = 0,R = 0,G = 0,B = 0;
    uint8_t i=0;
    float H =(float)(h),S=(float)(s)/100.0,V=(float)(v)/100.0;
    if(S == 0)
        R = G = B = V;
    else
    {
        H = H/60;
        i = (int)H;
        C = H - i;
        X = V * (1 - S);
        Y = V * (1 - S*C);
        Z = V * (1 - S*(1-C));
        switch(i){
            case 0 : R = V; G = Z; B = X; break;
            case 1 : R = Y; G = V; B = X; break;
            case 2 : R = X; G = V; B = Z; break;
            case 3 : R = X; G = Y; B = V; break;
            case 4 : R = Z; G = X; B = V; break;
            case 5 : R = V; G = X; B = Y; break;
        }
    }
    *r = (uint8_t)(R*255);
    *g = (uint8_t)(G*255);
    *b = (uint8_t)(B*255);
}
void getRGBWithBrightness(uint8_t r, uint8_t g, uint8_t b, uint8_t bright, uint8_t *resR, uint8_t *resG, uint8_t *resB){
	if(bright>100) bright = 100;
	uint16_t h, s, v;
	rgb_to_hsv(r,g,b,&h,&s,&v);
	v = (uint16_t)((float)v*(float)bright/100.0);
	hsv_to_rgb(h,s,v,resR,resG,resB);
}
void swap_u8(uint8_t *a, uint8_t *b){
	uint8_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap_u16(uint16_t *a, uint16_t *b){
	uint16_t temp = *a;
	*a = *b;
	*b = temp;
}

uint8_t getRandomNumber(uint8_t start, uint8_t end, uint8_t seedModifier){
	srand(HAL_GetTick()+seedModifier);
	return (rand()%(end-start+1))+start;
}
