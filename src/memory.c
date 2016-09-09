/*
 * memory.c
 *
 *  Created on: 2016. 8. 19.
 *      Author: songky08@gmail.com
 */

#include "memory.h"

#define BEGINSTACKADDR	0x70000000u		//starting point of heap
#define TASKSTACKSIZE	0x00000100u		//32byte

void mem_init(void)
{
	unsigned int pt = BEGINSTACKADDR;
	int i;

	for (i = 0; i < MAXMEMBLOCK; i++)
	{
		memblk[i].begin_addr_block = (Ifx_CPU_A)(pt + TASKSTACKSIZE - 4);
		memblk[i].end_addr_block = (Ifx_CPU_A)pt;
		memblk[i].flag = 0;
		pt += TASKSTACKSIZE;
	}
}

unsigned int mem_alloc(void)
{
	int i;

	for (i = 0; i < MAXMEMBLOCK; i++)
	{
		if (memblk[i].flag == 0)
		{
			memblk[i].flag = 1;
			return memblk[i].begin_addr_block.U;
		}
	}

	return 0;
}
