/*
 * main.c
 *
 *  Created on: 2016. 7. 30.
 *      Author: songky08@gmail.com
 */
#include "system.h"
#include "core.h"

extern int master_run(int argc, char **argv);

int main(int argc, char **argv)
{
	/* hardware initialisation */
	SYSTEM_Init();

	StartCore(1);
	StartCore(2);

	master_run(argc, argv);
	return 0;
}

