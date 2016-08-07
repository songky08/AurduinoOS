/*
 * usr_int.h
 *
 *  Created on: 2016. 8. 7.
 *      Author: songky08@gmail.com
 */

#ifndef USR_INT_H_
#define USR_INT_H_

#include "bspconfig.h"

#define GPT_ISR_PRIO	2
#define STM_ISR_PRIO	2
#define GPSR_ISR_PRO	8
#define SYSTIME_CLOCK	8	/* STM event rate [Hz] */

static Ifx_STM * const stm  = (Ifx_STM *)&MODULE_STM0;
static Ifx_GPT12 * const gpt12 = (Ifx_GPT12 *)&MODULE_GPT120;
static Ifx_INT* const ir = (Ifx_INT *)&MODULE_INT;

/* timer reload value (needed for subtick calculation) */
static unsigned int reload_value = 0;

/* timer interrupt routine function
 * arguments : reload_value renews compare value */
static void isrSTM(int reload_value);
static void isrGPT();
/* start General Purpose Service Request
 * arguments : x is group of SPSR
 * 			   y is member of group
 * 			   (*inthandler) is configured interrupt function */
int initGPSR(int x, int y, void(*inthandler));
void initGPT(unsigned int hz);
/* start timer processing function
 * initSTM function parameter configures frequency of interrupts
 * unit : hz */
void initSTM(unsigned int hz);

#endif /* USR_INT_H_ */
