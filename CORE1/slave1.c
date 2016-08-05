/*
 * slave1.c
 *
 *  Created on: 2016. 7. 28.
 *      Author: songky08@gmail.com
 */
#include "led.h"

int main_slave1(int argc, char **argv)
{
	pinMode(1, OUTPUT);
	digitalWrite(1, HIGH);	//check core1 is running

	while (1);
	return 0;
}
