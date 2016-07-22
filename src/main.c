/*
 * main.c
 *
 *      Author: songky08@gmail.com
 */

#include "led.h"
#include "spi.h"

int main()
{
	//assume 50Mhz
	serial_begin(9600);

	serial_write("serial write!!");
	return 0;
}
