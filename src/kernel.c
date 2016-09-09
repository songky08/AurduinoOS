/*
 * kernel.c
 *
 *  Created on: 2016. 9. 9.
 *      Author: songky08@gmail.com
 */
/*
 * kernel.h
 *
 *  Created on: 2016. 8. 27.
 *      Author: songky
 */

#include "kernel.h"

int get_current_tid()
{
	return running_task;
}

int insert_rq(int tid)
{
	if (running_task == -1)
	{
		running_task = tid;
	}
	else
	{
		readyQueue[running_task] = tid;
	}

	return 1;
}

inline void schedule()
{
	if (running_task != -1 && readyQueue[running_task] != -1)
	{
		int temp;

		readyQueue[readyQueue[running_task]] = running_task;
		temp = readyQueue[running_task];
		readyQueue[running_task] = -1;
		running_task = temp;

//		_mtcr(CPU0_A10, tmm.tcb[running_task].a[10]);
		__asm ("ji %0" :: "a"(tmm.tcb[get_current_tid()].a[11]));
	}
}

void StartOS(void)
{
	while(1);
}

inline void terminate(int tid)
{
	running_task = -1;
	if (readyQueue[tid] != -1)
	{
		__asm ("ji %0" :: "a"(tmm.tcb[readyQueue[tid]].pc));
	}
	else
	{
		__asm ("rslcx");
		__asm ("rfe");
	}
}
