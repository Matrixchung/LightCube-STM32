/*
 * oled.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Matrix
 */
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"

uint8_t OLED_GRAM[OLED_WIDTH][OLED_PAGE];

void I2C_Start(void){
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
}
void I2C_Stop(void){
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET);
	delay_us(2);
}
uint8_t I2C_WaitAck(void){
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
	delay_us(1);
	uint8_t ackTimeout = 0;
	while(HAL_GPIO_ReadPin(OLED_SDA_PORT, OLED_SDA_PIN)){
		ackTimeout++;
		if(ackTimeout>250){
			I2C_Stop();
			return 1;
		}
	}
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
	return 0;
}
void I2C_WriteByte(uint8_t data){
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
	for(uint8_t i = 0; i < 8; i++){
		HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, (data&0x80)>>7?GPIO_PIN_SET:GPIO_PIN_RESET);
		delay_us(2);
		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
		delay_us(2);
		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
		delay_us(2);
		data <<= 1;
	}
}
void OLED_WriteByte(uint8_t data, uint8_t cmd){
	// I2C ������ʽ
	if(USE_I2C){
		I2C_Start();
		I2C_WriteByte(0x78);
		I2C_WaitAck();
		I2C_WriteByte(cmd==1?0x40:0);
		I2C_WaitAck();
		I2C_WriteByte(data);
		I2C_WaitAck();
		I2C_Stop();
		return;
	}
    // SPI ������ʽ
//	HAL_GPIO_WritePin(OLED_DC_PORT, OLED_DC_PIN, cmd==1?GPIO_PIN_SET:GPIO_PIN_RESET);
//	for(uint8_t i=0;i<8;i++){
//		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, data&0x80?GPIO_PIN_SET:GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
//		data<<=1;
//	}
//	HAL_GPIO_WritePin(OLED_DC_PORT, OLED_DC_PIN, GPIO_PIN_SET);
}

void OLED_Display_On(void){
	OLED_WriteByte(0x8D, OLED_CMD); // SET DCDC
	OLED_WriteByte(0x14, OLED_CMD); // DCDC ON
	OLED_WriteByte(0xAF, OLED_CMD); // DISPLAY ON
}

void OLED_Display_Off(void){
	OLED_WriteByte(0x8D, OLED_CMD); // SET DCDC
	OLED_WriteByte(0x10, OLED_CMD); // DCDC OFF
	OLED_WriteByte(0xAE, OLED_CMD); // DISPLAY OFF
}
void OLED_RefreshGram(void){
	for(uint8_t i=0;i<OLED_PAGE;i++){
		OLED_WriteByte(0xB0+i, OLED_CMD); // ����ҳ��ַ
		OLED_WriteByte(0x00, OLED_CMD); // �����е͵�ַ
		OLED_WriteByte(0x10, OLED_CMD); // �����иߵ�ַ
		for(uint8_t j=0;j<OLED_WIDTH;j++) OLED_WriteByte(OLED_GRAM[j][i], OLED_DATA);
	}
}
void OLED_Clear(void){
	//for(uint8_t i=0;i<OLED_PAGE;i++) for(uint8_t j=0;j<OLED_WIDTH;j++) OLED_GRAM[j][i] = 0x00;
	memset(OLED_GRAM, 0, sizeof(OLED_GRAM));
	OLED_RefreshGram();
}
// state: 1: ��� 0: ���
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t state){
	if(x>OLED_WIDTH-1||y>OLED_HEIGHT-1) return; // ������Χ
	if(state) OLED_GRAM[x][7-y/8] |= (1<<(7-y%8));
	else OLED_GRAM[x][7-y/8] &= ~(1<<(7-y%8));
}
// size: 16: 1608���� 12: 1206����
// 1206: 12x6; 1608: 16x8
// mode: 0: ���� 1: ����
void OLED_DrawChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode){
	chr-=' '; // �ֿ���' '��Ӧ0
	uint8_t y0 = y;
	uint8_t temp = 0;
	if(size!=BIG_FONT&&size!=SMALL_FONT) size = SMALL_FONT;
	for(uint8_t i=0;i<size;i++){
		temp = size==BIG_FONT?oled_asc2_1608[chr][i]:oled_asc2_1206[chr][i];
		for(uint8_t j=0;j<8;j++){
			OLED_DrawPixel(x,y,temp&0x80?mode:!mode);
			temp<<=1;
			y++;
			if((y-y0)==size){
				y=y0;
				x++;
				break;
			}
		}
	}
}
void OLED_DrawNumber(uint8_t x, uint8_t y, uint32_t num, uint8_t size){
	uint8_t temp = 0, letter = 0;
	while(num>0){
		letter = num % 10;
		num /= 10;
		OLED_DrawChar(x+(size/2)*temp, y, letter+'0', size, 1);
		temp++;
	}
}
void OLED_DrawString(uint8_t x,uint8_t y, uint8_t size, const char *p)
{
    while(*p!='\0')
    {
        if(x>MAX_CHAR_POSX){x=0;y+=size;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_DrawChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }
}
void OLED_printf(uint8_t x, uint8_t y, uint8_t size, char *fmt, ...){
	char buffer[100];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, 100, fmt, args);
	OLED_DrawString(x, y, size, buffer);
	va_end(args);
}
void OLED_Init(void){
	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);
	OLED_WriteByte(0xAE, OLED_CMD); // �ر���ʾ
	OLED_WriteByte(0xD5, OLED_CMD); // ����ʱ�ӷ�Ƶ����, ��Ƶ��
	OLED_WriteByte(0x80, OLED_CMD); // [3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WriteByte(0xA8, OLED_CMD); // ��������·��
	OLED_WriteByte(0x3F, OLED_CMD); // Ĭ��0x3F(1/64)
	OLED_WriteByte(0xD3, OLED_CMD); // ������ʾƫ��
	OLED_WriteByte(0x00, OLED_CMD); // Ĭ��0

	OLED_WriteByte(0x40, OLED_CMD); // ������ʾ��ʼ�� [5:0], ����

	OLED_WriteByte(0x8D, OLED_CMD); // ��ɱ�����
	OLED_WriteByte(0x14, OLED_CMD); // Bit2, ����/�ر�
	OLED_WriteByte(0x20, OLED_CMD); // �����ڴ��ַģʽ
	OLED_WriteByte(0x02, OLED_CMD); // [1:0], 00,�е�ַģʽ; 01,�е�ַģʽ; 10,ҳ��ַģʽ; Ĭ��10;
	OLED_WriteByte(0xA1, OLED_CMD); // ���ض�������, bit0:0,0->0;1,0->127;
	OLED_WriteByte(0xC0, OLED_CMD); // ���� COM ɨ�跽��, bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WriteByte(0xDA, OLED_CMD); // ���� COM Ӳ����������
	OLED_WriteByte(0x12, OLED_CMD); // [5:4] ����

	OLED_WriteByte(0x81, OLED_CMD); // �Աȶ�����
	OLED_WriteByte(0xEF, OLED_CMD); // 1~255; Ĭ�� 0x7F (��������,Խ��Խ��)
	OLED_WriteByte(0xD9, OLED_CMD); // ����Ԥ�������
	OLED_WriteByte(0xF1, OLED_CMD); // [3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WriteByte(0xDB, OLED_CMD); // ���� VCOMH ��ѹ����
	OLED_WriteByte(0x30, OLED_CMD); // [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WriteByte(0xA4, OLED_CMD); // ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WriteByte(0xA6, OLED_CMD); // ������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ
	OLED_WriteByte(0xAF, OLED_CMD); // ������ʾ
	OLED_Clear();
}
