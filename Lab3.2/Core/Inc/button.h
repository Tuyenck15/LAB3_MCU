/*
 * button.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "software_timer.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

#define NUM_OF_BUTTONS 3			// Number of Buttons to use

int isButtonPressed(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */
