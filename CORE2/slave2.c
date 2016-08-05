/*
 * slave2.c
 *
 *  Created on: 2016. 7. 28.
 *      Author: songky08@gmail.com
 */
#include "led.h"

int main_slave2(int argc, char **argv)
{
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);	//check core 2 is running

	while (1);
	return 0;
}
