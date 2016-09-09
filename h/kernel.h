/*
 * kernel.h
 *
 *  Created on: 2016. 8. 27.
 *      Author: songky
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "task.h"

#define CPU0_A10	0xF881FFA8u

extern TMM tmm;

static int readyQueue[MAXTASKNUM] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
static int running_task = -1;

int get_current_tid();
int insert_rq(int tid);
inline void schedule();
/* Function of StartOS is just in loop */
void StartOS(void);
inline void terminate(int tid);

#endif /* KERNEL_H_ */
