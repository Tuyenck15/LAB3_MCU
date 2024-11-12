/*
 * button.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#include "button.h"

// Tao bien luu tru trang thai nut bam qua cac chu ky de kiem tra debouncing
int KeyReg0[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_OF_BUTTONS] = {NORMAL_STATE};

// Khoi tao flag cho nut bam
int button_flag[NUM_OF_BUTTONS] = {0}; //nhan thuong
int buttonlong_flag[NUM_OF_BUTTONS] = {0}; //nhan giu

// Bien dem de kiem tra thoi gian giu nut
int TimeOutForKeyPress[NUM_OF_BUTTONS] = {0};

// Kiem tra nut nhan cu the co duoc nhan hay khong
int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1; //Nut da duoc nhan
	}
	return 0;
}

void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput() {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];	// Xu li chong rung, neu tin hieu bang nhau qua nhieu chu ki tuc on dinh
		KeyReg1[i] = KeyReg2[i];

		// Doc cac tin hieu tu cac nut nhan
		if (i == 0) {
			KeyReg2[i] = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
		}
		else if (i == 1) {
			KeyReg2[i] = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
		}
		else if (i == 2) {
			KeyReg2[i] = HAL_GPIO_ReadPin(Button3_GPIO_Port, Button3_Pin);
		}

		// Xu li tin hieu
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE){
					subKeyProcess(i);	// Kich button_flag[i] = 1; nhấn thuong
					if (buttonlong_flag[i] == 0) { //giả sử chưa nhấn giu
						TimeOutForKeyPress[i] = 2000 / TIME_CYCLE; // thời gian chờ cho lần nhấn đầu (2 giây)
					}
					else {
						TimeOutForKeyPress[i] = 250 / TIME_CYCLE;  // Thiết lập thời gian chờ cho các lần tiếp theo (0.25 giây)
					}
				}
			} else {
				TimeOutForKeyPress[i]--;
				// Nếu hết thời gian và nút vẫn giữ
				if (TimeOutForKeyPress[i] == 0){
					KeyReg3[i] = NORMAL_STATE; // Đặt lại trạng thái
					buttonlong_flag[i] = 1; // Đánh dấu trạng thái giữ lâu
				}
			}
		}
		else {
			 // Nếu trạng thái không ổn định, đặt lại cờ giữ lâu
			buttonlong_flag[i] = 0;
		}
	}
}

