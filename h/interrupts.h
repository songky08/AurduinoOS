/*====================================================================
* Project:  Board Support Package (BSP)
* Function: Handling of interrupts on TC2x
*
* Copyright HighTec EDV-Systeme GmbH 1982-2014
*====================================================================*/

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__


#if defined(__TC29XX__)
#include "intids_tc29x.h"
#elif defined(__TC26XX__)
#include "intids_tc26x.h"
#elif defined(__TC27XX__)
#include "intids_tc27x.h"
#endif /* __TC29XX__ */


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* type of an Interrupt Service Routine (ISR) */
typedef void (*isrhnd_t)(int arg);


/*---------------------------------------------------------------------
	Function:	InterruptInit
	Purpose:	Initialisation of interrupt handling
	Arguments:	void
	Return:		void
---------------------------------------------------------------------*/
void InterruptInit(void);

/*---------------------------------------------------------------------
	Function:	InterruptInstall
	Purpose:	Install a service handler for an interrupt
	Arguments:	int irqNum       - number of interrupt
				isrhnd_t isrProc - pointer to service routine
				int prio         - priority (1-255)
				int arg          - argument for service routine
	Return:		void
---------------------------------------------------------------------*/
void InterruptInstall(int irqNum, isrhnd_t isrProc, int prio, int arg);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INTERRUPTS_H__ */
