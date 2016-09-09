/*
 * master.c
 *
 *  Created on: 2016. 7. 28.
 *      Author: songky08@gmail.com
 */
#include <machine/intrinsics.h>
#include "led.h"
#include "spi.h"
#include "core.h"
#include "usr_int.h"
#include "task.h"
#include "kernel.h"

extern void terminate(int tid);
extern void mem_init(void);

_Bool state;
int i;

void task1()
{
	static int i = 0;

	digitalWrite(3, i = !i);

	state = !state;

	terminate(0);
}

void task2()
{
	static int i = 0;

	digitalWrite(4, i = !i);

	state = !state;

	terminate(1);
}

void func()
{
	state = !state;
}

static void isrGPSR()
{
	//user code section
	_disable();

	_enable();
}

int master_run(int argc, char **argv)
{
	pinMode(0, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	digitalWrite(0, HIGH);	//check core0 is running

	mem_init();
	task_init();
	task_create(task1);
	task_create(task2);

	InterruptInit();
//	/* start timer processing */
	initSTM0(1);
	initSTM1(2);
	initGPSR(0, 0, isrGPSR);

	StartOS();

	return 0;
}
