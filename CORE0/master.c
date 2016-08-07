/*
 * master.c
 *
 *  Created on: 2016. 7. 28.
 *      Author: songky08@gmail.com
 */
#include "led.h"
#include "spi.h"
#include "core.h"
#include "interrupts.h"

#define GPT_ISR_PRIO	2
#define STM_ISR_PRIO	2
#define SYSTIME_CLOCK	8	/* STM event rate [Hz] */

static Ifx_STM * const stm  = (Ifx_STM *)&MODULE_STM0;
static Ifx_GPT12 * const gpt12 = (Ifx_GPT12 *)&MODULE_GPT120;

/* timer reload value (needed for subtick calculation) */
static unsigned int reload_value = 0;
_Bool stat = 0;

/* timer interrupt routine */
static void isrSTM(int reload_value)
{
	/* set new compare value */
	stm->CMP[0].U += (unsigned int)reload_value;

	stat = !stat;
}

static void isrGPT()
{
	//user code section
}

static void initGPT(unsigned int hz)
{
	unsigned int frequency = SYSTEM_GetSysClock();
	unsigned int reload_value = frequency / hz;

	InterruptInstall(SRC_ID_GPT120T2, isrGPT, GPT_ISR_PRIO, (int)reload_value);

	/* Enable Timer Mode */
	gpt12->T3CON.B.T3M = 0;
	/* Selects prescaler factor */
	gpt12->T3CON.B.T3I = 0;
	/* Timer T3 counts up */
	gpt12->T3CON.B.T3UD = 0;
	/* Enable Overflow/Underflow Output */
	gpt12->T3CON.B.T3OE = 1;
	/* Selects prescaler factor fgpt/8 */
	gpt12->T3CON.B.BPS1 = 0;
}
static void initSTM(unsigned int hz)
{
	unsigned int frequency = SYSTEM_GetStmClock();

	reload_value = frequency / hz;

	InterruptInstall(SRC_ID_STM0SR0, isrSTM, STM_ISR_PRIO, (int)reload_value);

	/* reset interrupt flag */
	stm->ISCR.U = (IFX_STM_ISCR_CMP0IRR_MSK << IFX_STM_ISCR_CMP0IRR_OFF);
	/* prepare compare register */
	stm->CMP[0].U = stm->TIM0.U + reload_value;
	stm->CMCON.B.MSIZE0 = 31;
	stm->ICR.B.CMP0EN = 1;
}

int master_run(int argc, char **argv)
{
	pinMode(3, OUTPUT);
	InterruptInit();
	/* start timer processing
	 * initSTM function parameter configures frequency of interrupts
	 * unit : hz */
	initSTM(1);

	pinMode(0, OUTPUT);
	digitalWrite(0, HIGH);	//check core0 is running

	serial_begin(9600);
	serial_write("%d\n", 1231);

	while(1)
	{
		if(stat)
		{
			digitalWrite(3, HIGH);
		}
		else
		{
			digitalWrite(3, LOW);
		}
	}

	return 0;
}
