/*
 * usr_int.c
 *
 *  Created on: 2016. 8. 7.
 *      Author: songky08@gmail.com
 */

#include "usr_int.h"

/* timer interrupt routine */
static void isrSTM(int reload_value)
{
	/* set new compare value */
	stm->CMP[0].U += (unsigned int)reload_value;

	//user code section
}

static void isrGPT()
{
	//user code section
}

int initGPSR(int x, int y, void(*inthandler))
{
	int GPSR_id, coordinates;

	if (x < 0 || x > 2 || y < 0 || y > 3)
	{
		return 0;	//fail
	}

	coordinates = 10 * x + y;
	switch(coordinates)
	{
	case 0:
		GPSR_id = SRC_ID_GPSR00;
		break;
	case 1:
		GPSR_id = SRC_ID_GPSR01;
		break;
	case 2:
		GPSR_id = SRC_ID_GPSR02;
		break;
	case 3:
		GPSR_id = SRC_ID_GPSR03;
		break;
	case 10:
		GPSR_id = SRC_ID_GPSR10;
		break;
	case 11:
		GPSR_id = SRC_ID_GPSR11;
		break;
	case 12:
		GPSR_id = SRC_ID_GPSR12;
		break;
	case 13:
		GPSR_id = SRC_ID_GPSR13;
		break;
	case 20:
		GPSR_id = SRC_ID_GPSR20;
		break;
	case 21:
		GPSR_id = SRC_ID_GPSR21;
		break;
	case 22:
		GPSR_id = SRC_ID_GPSR22;
		break;
	case 23:
		GPSR_id = SRC_ID_GPSR23;
		break;
	}

	InterruptInstall(GPSR_id, inthandler, GPSR_ISR_PRO, coordinates);

	return 1;	//complete initializing
}

/* =============================================================
 * start timer processing
 * initSTM function parameter configures frequency of interrupts
 * unit : hz
 * =============================================================*/
void initGPT(unsigned int hz)
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
void initSTM(unsigned int hz)
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
