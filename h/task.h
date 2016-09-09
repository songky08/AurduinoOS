/*
 * task.h
 *
 *  Created on: 2016. 8. 19.
 *      Author: songky08@gmail.com
 */

#ifndef TASK_H_
#define TASK_H_

#include <machine/_types.h>
#include <tc27xc/IfxCpu_regdef.h>

#define MAXTASKNUM	10

typedef struct _task_control_block
{
	unsigned int pcxi;	//previous context information register
	unsigned int psw;		//program status word register
	void (*tbody)(void);		//program counter
	unsigned int pc;
	unsigned int d[16];
	unsigned int a[16];	//a[10] = stack pointer, a[11] = return address
}TCB;

typedef struct _task_management
{
	TCB tcb[MAXTASKNUM];
	__uint32_t tcnt;

//	void (*init)(void);
//	int (*create)(void(*taskFunc)(void));
}TMM;

void task_init(void);
int task_create(void (*taskFunc)(void));

#endif /* TASK_H_ */
