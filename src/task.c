/*
 * task.c
 *
 *  Created on: 2016. 8. 19.
 *      Author: songky08@gmail.com
 */
#include "task.h"

TMM tmm;

int task_create(void (*taskFunc)(void))
{
	Ifx_CPU_A sp;

	if (tmm.tcnt + 1 > MAXTASKNUM)
	{
		return -1;
	}

	sp.U = mem_alloc();

	if (!sp.U)
	{
		return -2;
	}

	tmm.tcb[tmm.tcnt].a[10] = sp.U;
	tmm.tcb[tmm.tcnt].tbody = taskFunc;
	tmm.tcb[tmm.tcnt].pc = (unsigned int)taskFunc;

	return ++tmm.tcnt;
}

void task_init(void)
{
	int i;

	for (i = 0; i < MAXTASKNUM; i++)
	{
		memset(&tmm.tcb[i], 0, sizeof(tmm.tcb[i]));
	}
}
