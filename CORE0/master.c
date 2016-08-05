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

#define STM_ISR_PRIO	2
#define SYSTIME_CLOCK	8	/* STM event rate [Hz] */

static Ifx_STM * const stm  = (Ifx_STM *)&MODULE_STM0;

/* timer reload value (needed for subtick calculation) */
static unsigned int reload_value = 0;

/* timer interrupt routine */
static void isrSTM(int reload_value)
{
	/* set new compare value */
	stm->CMP[0].U += (unsigned int)reload_value;
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
	InterruptInit();
	/* start timer processing */
	initSTM(SYSTIME_CLOCK);

	pinMode(0, OUTPUT);
	digitalWrite(0, HIGH);	//check core0 is running

	while(1);

	return 0;
}
