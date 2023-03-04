/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../User_Drivers/USART/retarget.h"
#include "../../User_Drivers/USART/uart_callback.h"
#include "../../User_Drivers/Delay/delay.h"
#include "../../User_Drivers/Bluetooth/bluetooth.h"
#include "../../User_Drivers/OLED/oled.h"
#include "../../User_Drivers/WS2812/ws2812.h"
#include "../../User_Drivers/WS2812/animation.h"
#include "../../User_Drivers/Utils/utils.h"
#include "../../User_Drivers/Snake/snake.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEFAULT_ANIM_TIMES 5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t btConnected = 0;
uint8_t btStateChanged = 0;
uint8_t timer60_count = 0; // will be used in SysTick_Handler() in f4xx_it.c
uint8_t timer60 = 0; // Triggered (be set to 1) every 60 ticks
uint8_t timer15_count = 0; // will be used in SysTick_Handler() in f4xx_it.c
uint8_t timer15 = 0; // Triggered (be set to 1) every 15 ticks
uint8_t timer5_count = 0;
uint8_t timer5 = 0; // Triggered (be set to 1) every 5 ticks
uint8_t currentMode = 0;
uint8_t modeChanged = 0;
uint8_t dotPos[3] = {1, 1, 1};
uint8_t pwmDuty = 0;
uint8_t brightness = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void updateOLED(){
	if(modeChanged){
//		OLED_Clear();
		if(currentMode != 6 || currentMode != 8 || currentMode != 1 || currentMode != 9) OLED_printf(0,45,BIG_FONT,"                ");
		OLED_printf(28,0,BIG_FONT,"LightCube");
		if(btConnected) OLED_printf(120,0,BIG_FONT, "B");
		else OLED_printf(120,0,BIG_FONT, " ");
		switch(currentMode){
		case 0:
			OLED_printf(0,25,BIG_FONT,"                ");
			break;
		case 1:
			OLED_printf(0,25,BIG_FONT,"Mode: Single    ");
			OLED_printf(0,45,BIG_FONT,"Bright.: %d%%",brightness);
			break;
		case 2:
			OLED_printf(0,25,BIG_FONT,"Mode: All       ");
			break;
		case 3:
			OLED_printf(0,25,BIG_FONT,"Mode: Breathe   ");
			break;
		case 4:
			OLED_printf(0,25,BIG_FONT,"Mode: Gradient  ");
			break;
		case 5:
			OLED_printf(0,25,BIG_FONT,"Mode: Number    ");
			break;
		case 6:
			OLED_printf(0,25,BIG_FONT,"Mode: Dot       ");
			OLED_printf(0,45,BIG_FONT,"(%d, %d, %d)",dotPos[0],dotPos[1],dotPos[2]);
			break;
		case 7:
			OLED_printf(0,25,BIG_FONT,"Mode: Animation ");
			break;
		case 8:
			OLED_printf(0,25,BIG_FONT,"Mode: PWM Output"); // 1KHz
			OLED_printf(0,45,BIG_FONT,"Duty: %d%% @1KHz",pwmDuty);
			break;
		case 9:
			OLED_printf(0,25,BIG_FONT,"Mode: PWM Wave  "); // 1KHz
			OLED_printf(0,45,BIG_FONT,"Duty: Dynamic",pwmDuty);
			break;
		case 10:
			OLED_printf(0,25,BIG_FONT,"Mode: Snake Game");
			break;
		default: break;
		}
		OLED_RefreshGram();
		modeChanged = 0;
	}
	if(btStateChanged){
		if(btConnected) OLED_printf(120,0,BIG_FONT, "B");
		else OLED_printf(120,0,BIG_FONT, " ");
		OLED_RefreshGram();
		btStateChanged = 0;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//  uint16_t UART1_COMMAND_BUF[200] = {0};
//  uint8_t UART1_COMMAND_LEN = 0;
  uint16_t UART6_COMMAND_BUF[200] = {0};
  uint8_t UART6_COMMAND_LEN = 0;
  uint16_t DMA_ADC_BUF = 0; // Microphone ADC
  uint8_t dotRGB[3] = {255, 255, 255};
  uint16_t dotGradientTemp = 1;
  uint8_t dotShown = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  UART_RetargetInit(&huart1);
  UART1_SetCallback();
  UART6_SetCallback();
  OLED_Init();
  OLED_printf(28,0,BIG_FONT,"LightCube");
  OLED_RefreshGram();
  LED_Update();
//  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&DMA_ADC_BUF, 1);
  HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, pwmDuty * 100);
//  LED_Anim_Countdown(1);
  if(!HAL_GPIO_ReadPin(BT_STATE_GPIO_Port, BT_STATE_Pin)){
	  btStateChanged = 1;
	  btConnected = 1;
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	updateOLED();
	if(timer15){
		if(dotShown){
			if(dotGradientTemp>=359) dotGradientTemp = 1;
			else dotGradientTemp++;
			dotRGB[0] = gradientR[dotGradientTemp];
			dotRGB[1] = gradientG[dotGradientTemp];
			dotRGB[2] = gradientB[dotGradientTemp];
			LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
			LED_Update();
	//		hsv_to_rgb(dotGradientTemp, 100, 100, &dotRGB[0], &dotRGB[1], &dotRGB[2]);
		}
		timer15 = 0;
	}
	if(timer5){
		if(timer_game_count == GAME_SPEED/5 - 1){
			timer_game_count = 0;
			timer_game = 1;
		}else timer_game_count++;
		if(currentMode == 9){
//			modeChanged = 1;
			if(pwmDuty>99) pwmDuty = 0;
			else pwmDuty++;
//			updateOLED();
			__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, pwmDuty * 100);
		}
		timer5 = 0;
	}
	if(timer_game){
		if(currentMode == 10) {
			snakeUpdate();
			if(snake_game_state != 1) {
				currentMode = 0;
				modeChanged = 1;
				snake_dir_control = 0;
				snakeDelete();
			}
		}
		timer_game = 0;
	}
	if(UART6_Available()){
		switch(UART6_Read(0)){
		case 'w':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			switch(UART6_COMMAND_LEN){
			case 0:
				currentMode = 9;
				modeChanged = 1;
				pwmDuty = 0;
				BT_printf("Set PWM output at 0-100%% wave\n");
				updateOLED();
				__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, pwmDuty * 100);
				break;
			case 1:
				currentMode = 8;
				modeChanged = 1;
				pwmDuty = UART6_COMMAND_BUF[0];
				if(pwmDuty>100) pwmDuty = 100;
				BT_printf("Set PWM output at %d %% duty\n", pwmDuty);
				updateOLED();
				__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, pwmDuty * 100);
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'c':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			switch(UART6_COMMAND_LEN){
			case 3:
				modeChanged = 1;
				currentMode = 1;
				BT_printf("Set LED (%d, %d, %d) to WHITE at 100 %% Brightness\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				brightness = 100;
				updateOLED();
				LED_SetColor(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],255,255,255);
				LED_Update();
				break;
			case 4:
				modeChanged = 1;
				currentMode = 1;
				BT_printf("Set LED (%d, %d, %d) to WHITE at %d %% Brightness\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3]);
				brightness = UART6_COMMAND_BUF[3];
				uint8_t tempR,tempG,tempB;
				getRGBWithBrightness(255,255,255,brightness,&tempR,&tempG,&tempB);
				updateOLED();
				LED_SetColor(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],tempR,tempG,tempB);
				LED_Update();
				break;
			case 6:
				modeChanged = 1;
				currentMode = 1;
				BT_printf("Set LED (%d, %d, %d) to (%d, %d, %d)\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				updateOLED();
				LED_SetColor(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				LED_Update();
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'r':
			pwmDuty = 0;
			__HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, pwmDuty * 100);
			dotShown = 0;
			currentMode = 0;
			modeChanged = 1;
			BT_printf("Resetting all LEDs...\n");
			updateOLED();
//			LED_SetBrightness(DEFAULT_BRIGHTNESS);
			LED_ResetAll();
			snakeDelete();
			LED_Update();
			break;
		case 'a':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			switch(UART6_COMMAND_LEN){
			case 3:
				currentMode = 2;
				modeChanged = 1;
				BT_printf("Set all LED to (%d, %d, %d)\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				updateOLED();
				LED_SetColorAll(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				LED_Update();
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'b':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			switch(UART6_COMMAND_LEN){
			case 3:
				currentMode = 3;
				modeChanged = 1;
				BT_printf("Breathing LED (%d, %d, %d)...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				updateOLED();
				LED_BreatheOnePixel(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],350,25,1);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			case 5:
				currentMode = 3;
				modeChanged = 1;
				BT_printf("Breathing LED (%d, %d, %d) with H: %d, S: %d...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4]);
				updateOLED();
				LED_BreatheOnePixel(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],1);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			case 6:
				currentMode = 3;
				modeChanged = 1;
				BT_printf("Breathing LED (%d, %d, %d) with H: %d, S: %d for %d time(s)...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				updateOLED();
				LED_BreatheOnePixel(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			case 9:
				currentMode = 3;
				modeChanged = 1;
				BT_printf("Breathing LEDs from (%d, %d, %d) to (%d, %d, %d) with H: %d, S: %d for %d time(s)...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5],UART6_COMMAND_BUF[6],UART6_COMMAND_BUF[7],UART6_COMMAND_BUF[8]);
				updateOLED();
				LED_BreatheBatch(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5],UART6_COMMAND_BUF[6],UART6_COMMAND_BUF[7],UART6_COMMAND_BUF[8]);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'g':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			switch(UART6_COMMAND_LEN){
			case 3:
				currentMode = 4;
				modeChanged = 1;
				BT_printf("Gradient LED (%d, %d, %d)...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				updateOLED();
				LED_GradientOnePixel(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2]);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			case 6:
				currentMode = 4;
				modeChanged = 1;
				BT_printf("Gradient LEDs from (%d, %d, %d) to (%d, %d, %d)...\n", UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				updateOLED();
				LED_GradientBatch(UART6_COMMAND_BUF[0],UART6_COMMAND_BUF[1],UART6_COMMAND_BUF[2],UART6_COMMAND_BUF[3],UART6_COMMAND_BUF[4],UART6_COMMAND_BUF[5]);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'n':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			LED_ResetAll();
			switch(UART6_COMMAND_LEN){
			case 3:
				currentMode = 5;
				modeChanged = 1;
				BT_printf("Presenting number %d at #%d face, #%d layer\n", UART6_COMMAND_BUF[0], UART6_COMMAND_BUF[1], UART6_COMMAND_BUF[2]);
				updateOLED();
				LED_Anim_ShowNumber(UART6_COMMAND_BUF[0], UART6_COMMAND_BUF[1], UART6_COMMAND_BUF[2], COLOR_WHITE);
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				break;
			default: BT_printf("Wrong arguments!\n"); break;
			}
			break;
		case 'W':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_FRONT;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[1]<5) BT_printf("Moving to (%d, %d, %d)\n",dotPos[0],++dotPos[1],dotPos[2]);
				else BT_printf("Y coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
		case 'S':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_BACK;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[1]>1) BT_printf("Moving to (%d, %d, %d)\n",dotPos[0],--dotPos[1],dotPos[2]);
				else BT_printf("Y coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
		case 'A':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_LEFT;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[0]>1) BT_printf("Moving to (%d, %d, %d)\n",--dotPos[0],dotPos[1],dotPos[2]);
				else BT_printf("X coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
		case 'D':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_RIGHT;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[0]<5) BT_printf("Moving to (%d, %d, %d)\n",++dotPos[0],dotPos[1],dotPos[2]);
				else BT_printf("X coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
		case 'Q':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_UP;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[2]<5) BT_printf("Moving to (%d, %d, %d)\n",dotPos[0],dotPos[1],++dotPos[2]);
				else BT_printf("Z coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
		case 'E':
			if(currentMode == 10) {
				snake_dir_control = SNAKE_DIR_DOWN;
				timer_game_count = 0; // reset the timer
				snakeUpdate();
			}
			else{
				LED_ResetAll();
				dotShown = 1;
				currentMode = 6;
				modeChanged = 1;
				if(dotPos[2]>1) BT_printf("Moving to (%d, %d, %d)\n",dotPos[0],dotPos[1],--dotPos[2]);
				else BT_printf("Z coordinate reached boundary!\n");
				updateOLED();
				LED_SetColor(dotPos[0],dotPos[1],dotPos[2],dotRGB[0],dotRGB[1],dotRGB[2]);
				LED_Update();
			}
			break;
//		case 'l':
//			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
//			if(UART6_COMMAND_LEN==1){
//				BT_printf("LED brightness has been set to %d %%\n",UART6_COMMAND_BUF[0]);
//				LED_SetBrightness(UART6_COMMAND_BUF[0]);
//				brightness = UART6_COMMAND_BUF[0];
//			} else BT_printf("Wrong arguments!\n");
//			break;
		case 'p':
			splitData(UART6_GetBufferPtr(), UART6_ReceivedLength(), UART6_COMMAND_BUF, &UART6_COMMAND_LEN, ' ');
			if(UART6_COMMAND_LEN==1||UART6_COMMAND_LEN==2){
				currentMode = 7;
				modeChanged = 1;
				updateOLED();
				uint8_t times = UART6_COMMAND_LEN==2?UART6_COMMAND_BUF[1]:DEFAULT_ANIM_TIMES;
				BT_printf("Presenting #%d anim for %d times..\n",UART6_COMMAND_BUF[0],times);
				switch(UART6_COMMAND_BUF[0]){
				case 1:
					LED_Anim_GradientLayer(times);
					break;
				case 2:
					LED_Anim_FlashLayer(times);
					break;
				case 3:
					LED_Anim_Heart(times);
					break;
				case 4:
					LED_Anim_Rain(times);
					break;
				case 5:
					LED_Anim_CycleOnOff(times);
					break;
				case 6:
					LED_Anim_RainbowWave(times);
					break;
				case 7:
					LED_Anim_Countdown(times);
					break;
				case 8:
					LED_Anim_Snake(times);
					break;
				default: BT_printf("Wrong arguments!\n"); break;
				}
				currentMode = 0;
				modeChanged = 1;
				updateOLED();
				LED_ResetAll();
				LED_Update();
			}
			else BT_printf("Wrong arguments!\n");
			break;
		case 's':
			currentMode = 10;
			modeChanged = 1;
			snake_game_state = 1;
			BT_printf("Entering Snake Game...\n");
			updateOLED();
			LED_ResetAll();
			snakeInit();
			break;
		default:
			BT_printf("UART6 Received: ");
			for(uint8_t i=0;i<UART6_ReceivedLength();i++) {
				BT_printf("%c",UART6_Read(i));
			}
			break;
		}
	  	UART6_Clear();
	}
	if(btStateChanged){
		if(btConnected) printf("Bluetooth connected.\n");
		else printf("Bluetooth disconnected.\n");
		updateOLED();
		btStateChanged = 0;
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 24;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin){
	case BT_STATE_Pin:
		btConnected = !HAL_GPIO_ReadPin(BT_STATE_GPIO_Port, BT_STATE_Pin);
		btStateChanged = 1;
		break;
	default: break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
