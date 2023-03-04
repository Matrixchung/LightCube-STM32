/*
 * snake.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Matrix
 */
#include "snake.h"

uint8_t timer_game = 0;
uint16_t timer_game_count = 0; // be added up in timer5(ticks) for GAME_SPEED(ms)/5 ticks, then call timer_game
uint8_t snake_dir_control = 0; // 0 - none, 1 - front, 2 - back, 3 - left, 4 - right, 5 - up, 6 - down
uint8_t snake_game_state = 0;  // 0 - none, 1 - running, 2 - win, 3 - lose


// Food = -1,
// Snake Head = 1, Snake Body > 1
int8_t map[SNAKE_BOARD_X+1][SNAKE_BOARD_Y+1][SNAKE_BOARD_Z+1] = {0};
uint8_t snakeLength = 1;
uint8_t snakeDir = 0;
uint8_t foodCount = 1;
void _updateMapColor(){
	for(uint8_t x = 1; x <= SNAKE_BOARD_X; x++){
		for(uint8_t y = 1; y <= SNAKE_BOARD_Y; y++){
			for(uint8_t z = 1; z <= SNAKE_BOARD_Z; z++){
				if(map[x][y][z] > 0){
					if(map[x][y][z] == 1) LED_SetColor(x,y,z,255,255,0);
					else LED_SetColor(x,y,z,255,0,0);
				}
				else if(map[x][y][z] == 0) LED_SetColor(x,y,z,0,0,0);
				else{
					if(map[x][y][z] == -1) LED_SetColor(x,y,z,0,255,255);
				}
			}
		}
	}
}
uint8_t t1, t2, t3 = 0;
void snakeInit(){
//	Snake.length = 1;
//	Snake.pos[0][0] = Snake.pos[0][1] = Snake.pos[0][2] = 3;
//	Snake.dir = SNAKE_DIR_FRONT;
//	for(uint8_t i = 0; i < Snake.length; i++) LED_SetColor(Snake.pos[i][0],Snake.pos[i][1],Snake.pos[i][2],255,255,255);
	map[3][3][3] = 1; // snake head
//	map[2][2][2] = -1; // test food
	do{
		t1 = getRandomNumber(1,4,2);
		t2 = getRandomNumber(1,4,6);
		t3 = getRandomNumber(1,4,11);
	}while(map[t1][t2][t3]>0);
	map[t1][t2][t3] = -1;
	foodCount = 1;
//	map[getRandomNumber(1,4)][getRandomNumber(1,4)][getRandomNumber(1,4)] = -1;
	snakeDir = SNAKE_DIR_FRONT;
	_updateMapColor();
	LED_Update();
}

void snakeUpdate(){
	// Update snake.pos[0], Delete snake.pos[length]
//	HAL_GPIO_TogglePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin);
	LED_ResetAll();
	if(snake_dir_control){
		snakeDir = snake_dir_control;
		snake_dir_control = 0;
	}
	if(!foodCount){
		do{
			t1 = getRandomNumber(1,4,66);
			t2 = getRandomNumber(1,4,12);
			t3 = getRandomNumber(1,4,33);
		}while(map[t1][t2][t3]>0);
		map[t1][t2][t3] = -1;
		foodCount++;
	}
	for(uint8_t x = 1; x <= SNAKE_BOARD_X; x++){
		for(uint8_t y = 1; y <= SNAKE_BOARD_Y; y++){
			for(uint8_t z = 1; z <= SNAKE_BOARD_Z; z++){
				if(map[x][y][z]>0) map[x][y][z]++;
			}
		}
	}
	for(uint8_t x = 1; x <= SNAKE_BOARD_X; x++){
		for(uint8_t y = 1; y <= SNAKE_BOARD_Y; y++){
			for(uint8_t z = 1; z <= SNAKE_BOARD_Z; z++){
				if(map[x][y][z] == 2){ // old head
					switch(snakeDir){
					case SNAKE_DIR_NONE:
						break;
					case SNAKE_DIR_FRONT:
						if(y<SNAKE_BOARD_Y){
							if(map[x][y+1][z] == -1) {
								snakeLength++;
								foodCount--;
							}
							map[x][y+1][z] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					case SNAKE_DIR_BACK:
						if(y>1&&map[x][y-1][z]<=0){
							if(map[x][y-1][z] == -1){
								snakeLength++;
								foodCount--;
							}
							map[x][y-1][z] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					case SNAKE_DIR_UP:
						if(z<SNAKE_BOARD_Z) {
							if(map[x][y][z+1] == -1) {
								snakeLength++;
								foodCount--;
							}
							map[x][y][z+1] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					case SNAKE_DIR_DOWN:
						if(z>1) {
							if(map[x][y][z-1] == -1){
								snakeLength++;
								foodCount--;
							}
							map[x][y][z-1] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					case SNAKE_DIR_LEFT:
						if(x>1) {
							if(map[x-1][y][z] == -1){
								snakeLength++;
								foodCount--;
							}
							map[x-1][y][z] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					case SNAKE_DIR_RIGHT:
						if(x<SNAKE_BOARD_X) {
							if(map[x+1][y][z] == -1) {
								snakeLength++;
								foodCount--;
							}
							map[x+1][y][z] = 1;
						}
						else{
							snake_game_state = 3;
							snakeDelete();
						}
						break;
					default: break;
					}
				}
				if(map[x][y][z] == snakeLength + 1) map[x][y][z] = 0;
			}
		}
	}
	_updateMapColor();
	LED_Update();
//	switch(Snake.dir){
//	case SNAKE_DIR_NONE:
//		Snake.pos[0][0] = Snake.pos[0][1] = Snake.pos[0][2] = 0;
//		break;
//	case SNAKE_DIR_FRONT: // y+1
//		if(Snake.pos[0][1]<SNAKE_BOARD_Y){
//			LED_SetColor(Snake.pos[Snake.length-1][0],Snake.pos[Snake.length-1][1],Snake.pos[Snake.length-1][2],0,0,0);
//			move_list_elements_behind(Snake.pos, Snake.length);
//			Snake.pos[0][0] = Snake.pos[1][0];
//			Snake.pos[0][1] = Snake.pos[1][1]+1;
//			Snake.pos[0][2] = Snake.pos[1][2];
//			for(uint8_t i = 0; i < Snake.length; i++) LED_SetColor(Snake.pos[i][0],Snake.pos[i][1],Snake.pos[i][2],255,255,255);
//			LED_Update();
//		}
//		else{ // reached maximum Y
//			;
//		}
//		break;
//	case SNAKE_DIR_BACK: // y-1
//
//		break;
//	case SNAKE_DIR_LEFT:
//		break;
//	default: break;
//	}
}

void snakeDelete(){
	snakeDir = 0;
	snakeLength = 1;
	memset(map, 0, SNAKE_BOARD_X*SNAKE_BOARD_Y*SNAKE_BOARD_Z);
	LED_ResetAll();
	LED_Update();
}
