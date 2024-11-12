/*
 * display.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#include <led-7segment.h>

void display7SEG(int counter) {
	/* Khoi tao mot day gom gia tri bit de hien thi cac chu so lan luot tu 0 toi 9 */
	unsigned char disp_arr[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
	/* Khoi tao bien "varr" chua gia tri bit 7 doan cua bien "counter" de hien thi con so can hien thi va bien "bit_var" */
	unsigned char bit_var, varr = disp_arr[counter];

	/* Doi voi tung doan segment, bien bit_var se lay gia tri bit cua segment do de hien thi den (0 -> Sang, 1 -> Tat) */

	bit_var = varr & 0x01; /* Den SEG0 */
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, bit_var);

	bit_var = (varr>>1) & 0x01; /* Den SEG1 */
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, bit_var);

	bit_var = (varr>>2) & 0x01; /* Den SEG2 */
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, bit_var);

	bit_var = (varr>>3) & 0x01; /* Den SEG3 */
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, bit_var);

	bit_var = (varr>>4) & 0x01; /* Den SEG4 */
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, bit_var);

	bit_var = (varr>>5) & 0x01; /* Den SEG5 */
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, bit_var);

	bit_var = (varr>>6) & 0x01; /* Den SEG6 */
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, bit_var);
}

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
void update7SEG(int index){
	display7SEG(led_buffer[index]);
	switch(index){
	case 0:
		// Display the second 7 SEG with led_buffer[0]
		index_led = 1;
		HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, RESET);
		HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, SET);
		HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, SET);
		HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, SET);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer[1]
		index_led = 2;
		HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, SET);
		HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, RESET);
		HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, SET);
		HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, SET);
		break;
	case 2:
		// Display the third 7 SEG with led_buffer[2]
		index_led = 3;
		HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, SET);
		HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, SET);
		HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, RESET);
		HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, SET);
		break;
	case 3:
		// Display the forth 7 SEG with led_buffer[3]
		index_led = 0;
		HAL_GPIO_WritePin(V1_GPIO_Port, V1_Pin, SET);
		HAL_GPIO_WritePin(V2_GPIO_Port, V2_Pin, SET);
		HAL_GPIO_WritePin(H1_GPIO_Port, H1_Pin, SET);
		HAL_GPIO_WritePin(H2_GPIO_Port, H2_Pin, RESET);
		break;
	default:
		break;
	}
}


int counterH = 1, counterV = 1;
void updateClockBufferMode1() {
	// Cap nhat gia tri thoi gian vao trong clockBuffer
	// Doi voi 2 LED 7-SEG Horizontal

	/* Den RED-Horizontal sang (dem nguoc tu RED-1 -> 0) */
	if (counterH <= RED) {
		led_buffer[0] = (RED - counterH) / 10;
		led_buffer[1] = (RED - counterH) % 10;
	}
	/* Den GREEN-Horizontal sang (dem nguoc tu GREEN-1 -> 0) */
	else if (counterH <= (RED + GREEN)) {
		led_buffer[0] = (RED + GREEN - counterH) / 10;
		led_buffer[1] = (RED + GREEN - counterH) % 10;
	}
	/* Den AMBER-Horizontal sang (dem nguoc tu AMBER-1 -> 0) */
	else {
		led_buffer[0] = (RED + GREEN + AMBER - counterH) / 10;
		led_buffer[1] = (RED + GREEN + AMBER - counterH) % 10;
	}
	counterH++;
	/* Neu thoi gian AMBER-Horizontal ket thuc, quay tro lai setup thoi gian cho RED-Horizontal sang lai */
	if (counterH > RED + AMBER + GREEN) counterH = 1;


	// Doi voi 2 LED 7-SEG Vertical
	/* Den GREEN-Vertical sang (dem nguoc tu GREEN-1 -> 0) */
	if (counterV <= GREEN) {
		led_buffer[2] = (GREEN - counterV) / 10;
		led_buffer[3] = (GREEN - counterV) % 10;
	}
	/* Den AMBER-Vertical sang (dem nguoc tu AMBER-1 -> 0) */
	else if (counterV <= (AMBER + GREEN)) {
		led_buffer[2] = (AMBER + GREEN - counterV) / 10;
		led_buffer[3] = (AMBER + GREEN - counterV) % 10;
	}
	/* Den RED-Vertical sang (dem nguoc tu RED-1 -> 0) */
	else {
		led_buffer[2] = (RED + GREEN + AMBER - counterV) / 10;
		led_buffer[3] = (RED + GREEN + AMBER - counterV) % 10;
	}
	counterV++;
	/* Neu thoi gian RED-Vertical ket thuc, quay tro lai setup thoi gian cho GREEN-Vertical sang lai */
	if (counterV > RED + AMBER + GREEN) counterV = 1;
}

void updateClockBufferMode2() {
	// Hien thi mode 2
	led_buffer[0] = 0;
	led_buffer[1] = 2;
	// Hien thi value RED
	led_buffer[2] = RED / 10;
	led_buffer[3] = RED % 10;
}

void updateClockBufferMode3() {
	// Hien thi mode 3
	led_buffer[0] = 0;
	led_buffer[1] = 3;
	// Hien thi value AMBER
	led_buffer[2] = AMBER / 10;
	led_buffer[3] = AMBER % 10;
}

void updateClockBufferMode4() {
	// Hien thi mode 4
	led_buffer[0] = 0;
	led_buffer[1] = 4;
	// Hien thi value GREEN
	led_buffer[2] = GREEN / 10;
	led_buffer[3] = GREEN % 10;
}

