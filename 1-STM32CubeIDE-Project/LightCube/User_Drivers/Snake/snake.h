/*
 * snake.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Matrix
 */

#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_

#include "main.h"
#include "../WS2812/ws2812.h"
#include "../Utils/utils.h"

#define GAME_SPEED 1500 // ms, higher means slower

#define SNAKE_LENGTH_INIT 1
#define SNAKE_MAX_LEN 10
#define OBSTACLES_MAX_COUNT 5
#define SNAKE_BOARD_X 5
#define SNAKE_BOARD_Y 5
#define SNAKE_BOARD_Z 5

// 0 - none, 1 - front, 2 - back, 3 - left, 4 - right, 5 - up, 6 - down
#define SNAKE_DIR_NONE 0
#define SNAKE_DIR_FRONT 1
#define SNAKE_DIR_BACK 2
#define SNAKE_DIR_LEFT 3
#define SNAKE_DIR_RIGHT 4
#define SNAKE_DIR_UP 5
#define SNAKE_DIR_DOWN 6



extern uint8_t timer_game;
extern uint16_t timer_game_count;

extern uint8_t snake_dir_control, snake_game_state;

void snakeUpdate();
void snakeInit();
void snakeDelete();

#endif /* SNAKE_SNAKE_H_ */
