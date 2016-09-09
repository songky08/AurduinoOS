/*
 * memory.h
 *
 *  Created on: 2016. 8. 19.
 *      Author: songky08@gmail.com
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <machine/_types.h>
#include <tc27xc/IfxCpu_regdef.h>

#define MAXMEMBLOCK	32

typedef struct _memory_block
{
	Ifx_CPU_A begin_addr_block;
	Ifx_CPU_A end_addr_block;
	__uint32_t flag;
}MEMBLK;

MEMBLK memblk[MAXMEMBLOCK];

void mem_init(void);
unsigned int mem_alloc(void);

#endif /* MEMORY_H_ */
