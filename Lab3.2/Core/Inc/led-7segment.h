/*
 * display.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#ifndef INC_LED_7SEGMENT_H_
#define INC_LED_7SEGMENT_H_

#include "main.h"
#include "global.h"

extern int index_led;
extern int counterH, counterV; //Horizontal, Vertical

void display7SEG(int counter);
void update7SEG(int index);

void updateClockBufferMode1();
void updateClockBufferMode2();
void updateClockBufferMode3();
void updateClockBufferMode4();

#endif /* INC_LED_7SEGMENT_H_ */
