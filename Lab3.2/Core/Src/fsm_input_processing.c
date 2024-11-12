/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#include <fsm_input_processing.h>

void fsm_input_processing() {
	switch(status){

//----------------------------------------------------------------------------------------------
	// Initial Mode Setup
	case INIT:
		status = MODE1; // Chuyển đổi sang mode1
		break;


	case MODE1:
		// Hien thi trang thai period AUTO_REDH_GREENV

		status = AUTO_REDH_GREENV;

		// Setup cho den Horizontal_RED va Vertical_GREEN sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, RESET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, SET);
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, SET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, SET);
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, SET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, RESET);

		// Cau hinh ban dau cho led-7segment (led-7segment.c)
		counterH = 1;
		counterV = 1;
		index_led = 0;
		updateClockBufferMode1();
		update7SEG(index_led);

		// Set Timer
		setTimer(0, GREEN * 1000);	// Timer cho 1 den nao do can dem nguoc
		setTimer(1, 1000);			// Timer updateClockBufferMode1
		setTimer(2, 250);			// Timer quet LED 7-SEG
		clearTimer(3);				// Timer cho blinking LED

		break;

	case AUTO_REDH_GREENV:
		// Cai dat den Horizontal_RED va Vertical_GREEN sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, RESET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, SET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, SET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDH_AMBERV dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDH_AMBERV;
			setTimer(0, AMBER * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDH_AMBERV:
		// Setup cho den Horizontal_RED va Vertical_AMBER sang
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, RESET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, SET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_GREENL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDV_GREENH;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDV_GREENH:
		// Setup cho den Vertical_RED va Horizontal_GREEN sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, SET);
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, SET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, RESET);
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDP_AMBERL dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDV_AMBERH;
			setTimer(0, AMBER * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;

	case AUTO_REDV_AMBERH:
		// Setup cho den Vertical_RED va Horizontal_AMBER sang
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, SET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, RESET);
		// Neu timer_flag[0] == 1, chuyen den trang thai AUTO_REDH_GREENV dong thoi setTimer cho truong hop ke tiep
		if (timer_flag[0] == 1) {
			status = AUTO_REDH_GREENV;
			setTimer(0, GREEN * 1000);
		}
		// Neu timer_flag[1] == 1, update gia tri thoi gian dem nguoc va setTimer lai
		if (timer_flag[1] == 1) {
			updateClockBufferMode1();
			setTimer(1, 1000);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan tiep theo va setTimer lai
		if (timer_flag[2] == 1) {
			update7SEG(index_led);
			setTimer(2, 250);
		}
		// Neu nhan nut MODE, he thong chuyen sang mode 2
		if (isButtonPressed(0) == 1) {
			status = MODE2;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 2
	case MODE2:
		// Setup cho tat ca cac den RED sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, RESET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, RESET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, SET);
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, SET);
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, SET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, SET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-RED
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_RED
		status = AUTO_RED;

		break;

	case AUTO_RED:
		// Neu timer_flag[3] == 1, toggle tat ca cac den RED va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HR_GPIO_Port, HR_Pin);
			HAL_GPIO_TogglePin(VR_GPIO_Port, VR_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// Neu nhan nut Button1 (MODE), he thong chuyen sang trang thai mode 3
		if (isButtonPressed(0) == 1) {
			status = MODE3;
		}
		// Neu nhan nut Button2 (INC), thay doi gia tri thoi gian RED, dong thoi chuyen sang trang thai INC_RED
		if (isButtonPressed(1) == 1) {
			status = INC_RED;
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		break;

	case INC_RED:
		// Neu timer_flag[3] == 1, toggle tat ca cac den RED va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HR_GPIO_Port, HR_Pin);
			HAL_GPIO_TogglePin(VR_GPIO_Port, VR_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian RED
		if (isButtonPressed(1) == 1) {
			if (RED >= 99) RED = AMBER + 1;
			else RED++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian RED, quay tro ve trang thai AUTO_RED, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_RED;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 3
	case MODE3:
		// Setup cho tat ca cac den AMBER sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, SET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, SET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, RESET);
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, RESET);
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, SET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, SET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-AMBER
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_AMBER
		status = AUTO_AMBER;
		break;

	case AUTO_AMBER:
		// Neu timer_flag[3] == 1, toggle tat ca cac den AMBER va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HA_GPIO_Port, HA_Pin);
			HAL_GPIO_TogglePin(VA_GPIO_Port, VA_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 4
		if (isButtonPressed(0) == 1) {
			status = MODE4;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian AMBER, dong thoi chuyen sang trang thai INC_AMBER
		if (isButtonPressed(1) == 1) {
			status = INC_AMBER;
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		break;

	case INC_AMBER:
		// Neu timer_flag[3] == 1, toggle tat ca cac den AMBER va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HA_GPIO_Port, HA_Pin);
			HAL_GPIO_TogglePin(VA_GPIO_Port, VA_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian AMBER, dong thoi chuyen sang trang thai INC_AMBER
		if (isButtonPressed(1) == 1) {
			if (AMBER >= 5) AMBER = 1;
			else AMBER++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian AMBER, quay tro ve trang thai AUTO_AMBER, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_AMBER;
			if (RED <= AMBER) RED = AMBER + 1;
			GREEN = RED - AMBER;
		}
		break;
//----------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------
// MODE 4
	case MODE4:
		// Setup cho tat ca cac den GREEN sang
		HAL_GPIO_WritePin(HR_GPIO_Port, HR_Pin, SET);
		HAL_GPIO_WritePin(VR_GPIO_Port, VR_Pin, SET);
		HAL_GPIO_WritePin(HA_GPIO_Port, HA_Pin, SET);
		HAL_GPIO_WritePin(VA_GPIO_Port, VA_Pin, SET);
		HAL_GPIO_WritePin(HG_GPIO_Port, HG_Pin, RESET);
		HAL_GPIO_WritePin(VG_GPIO_Port, VG_Pin, RESET);
		// Update lai gia tri hien thi ra LED 7 doan
		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);
		// SetTimer
		setTimer(2, 250);	// Timer de quet LED 7 doan dong thoi update lai buffer
		setTimer(3, 500);	// Timer blinking LED-GREEN
		clearTimer(0);		// O mode nay khong su dung timer de hien thi den o che do normal-mode
		clearTimer(1);		// Khong can su dung timer de update buffer moi giay
		// Chuyen ve trang thai AUTO_GREEN
		status = AUTO_GREEN;
		break;

	case AUTO_GREEN:
		// Neu timer_flag[3] == 1, toggle tat ca cac den GREEN va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HG_GPIO_Port, HG_Pin);
			HAL_GPIO_TogglePin(VG_GPIO_Port, VG_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// Neu nhan nut MODE, he thong chuyen sang trang thai mode 1
		if (isButtonPressed(0) == 1) {
			status = MODE1;
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian GREEN, dong thoi chuyen sang trang thai INC_GREEN
		if (isButtonPressed(1) == 1) {
			status = INC_GREEN;
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		break;

	case INC_GREEN:
		// Neu timer_flag[3] == 1, toggle tat ca cac den GREEN va setTimer lai
		if (timer_flag[3] == 1) {
			setTimer(3, 500);
			HAL_GPIO_TogglePin(HG_GPIO_Port, HG_Pin);
			HAL_GPIO_TogglePin(VG_GPIO_Port, VG_Pin);
		}
		// Neu timer_flag[2] == 1, quet sang LED 7 doan khac, update lai buffer va setTimer lai
		if (timer_flag[2] == 1) {
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}
		// Neu nhan nut INC, thay doi gia tri thoi gian GREEN, dong thoi chuyen sang trang thai INC_GREEN
		if (isButtonPressed(1) == 1) {
			if (GREEN >= RED - AMBER) GREEN = 1;
			else GREEN++;
		}
		// Neu nhan nut SET, co dinh gia tri thoi gian GREEN, quay tro ve trang thai AUTO_GREEN, dong thoi cap nhat lai bo ba gia tri thoi gian RED, AMBER va GREEN
		if (isButtonPressed(2) == 1) {
			status = AUTO_GREEN;
			RED = GREEN + AMBER;
		}
		break;
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// DEFAULT
	default:
		break;
	}
}

