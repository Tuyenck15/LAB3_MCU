/*
 * software_timer.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define NUM_OF_TIMERS 	4  				// Number of Timers to use

extern int TIME_CYCLE;					// Time cycle

extern int timer_flag[NUM_OF_TIMERS];

void setTimer(int index, int duration);
void clearTimer(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
