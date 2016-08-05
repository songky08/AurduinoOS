/*
 * led.h
 *
 *      Author: songky08@gmail.com
 */

#ifndef LED_H_
#define LED_H_

#include "bspconfig.h"

#define HIGH	1
#define LOW		0
#define MAX_LED	54
#define OUTPUT	0x10

void pinMode (int pin, int mode);
void digitalWrite(int pin, int sig);

#endif /* LED_H_ */
