/*====================================================================
* Project:  Board Support Package (BSP)
* Function: TriCore interrupt table
*
* Copyright HighTec EDV-Systeme GmbH 1982-2013
*====================================================================*/

#include "cint.h"

/* This structure describes interrupt handlers and their arguments.  */

typedef struct _Hnd_arg
{
	void (*hnd_handler)(int);
	int hnd_arg;
} Hnd_arg;


/* This array holds the functions to be called when an interrupt occurs.  */

Hnd_arg Cdisptab_CPU0[MAX_INTRS];
Hnd_arg Cdisptab_CPU1[MAX_INTRS];
Hnd_arg Cdisptab_CPU2[MAX_INTRS];
