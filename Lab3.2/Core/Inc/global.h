/*
 * global.h
 *
 *  Created on: Nov 4, 2024
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#define INIT				0
#define MODE1				1
#define MODE2				2
#define MODE3				3
#define MODE4				4

#define AUTO_REDH_GREENV	11
#define AUTO_REDH_AMBERV	12
#define AUTO_REDV_GREENH	13
#define	AUTO_REDV_AMBERH	14

#define AUTO_RED			21
#define INC_RED				22

#define AUTO_AMBER			31
#define INC_AMBER			32

#define AUTO_GREEN			41
#define INC_GREEN			42

extern int status;

extern int RED;
extern int AMBER;
extern int GREEN;

#endif /* INC_GLOBAL_H_ */
