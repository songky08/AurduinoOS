/*
 * spi.c
 *
 *  Created on: 2016. 7. 22.
 *      Author: songky
 */
#include "bspconfig.h"
#include "spi.h"

void serial_begin(int baud)
{
	P15_IOCR4.B.PC7 = 0x12;
	P15_OUT.B.P7 = 0;

	ASCLIN3_CLC.U = 0;
	ASCLIN3_CLC.U;
	ASCLIN3_IOCR.B.ALTI = 1;
	ASCLIN3_IOCR.B.LB = 0;
	ASCLIN3_CSR.U = 0;
	ASCLIN3_TXFIFOCON.B.INW = 1;
	ASCLIN3_TXFIFOCON.B.ENO = 1;
	ASCLIN3_TXFIFOCON.B.FLUSH = 1;
	ASCLIN3_RXFIFOCON.B.OUTW = 1;
	ASCLIN3_RXFIFOCON.B.ENI = 1;
	ASCLIN3_RXFIFOCON.B.FLUSH = 1;
	ASCLIN3_BITCON.B.PRESCALER = 9;
	ASCLIN3_BITCON.B.OVERSAMPLING = 0xF;
	ASCLIN3_BITCON.B.SAMPLEPOINT = 8;
	ASCLIN3_BITCON.B.SM = 1;
	ASCLIN3_FRAMECON.B.STOP = 1;
	ASCLIN3_FRAMECON.B.LEAD = 1;
	ASCLIN3_FRAMECON.B.MODE = 0;
	ASCLIN3_FRAMECON.B.PEN = 0;
	ASCLIN3_FRAMECON.B.MSB = 0;
	ASCLIN3_DATCON.B.DATLEN = 7;
	ASCLIN3_BRG.B.DENOMINATOR = 3125;
	ASCLIN3_BRG.B.NUMERATOR = baud / 100;
	ASCLIN3_FRAMECON.B.MODE = 2;
	ASCLIN3_CSR.B.CLKSEL = 1;

	ASCLIN3_FLAGSSET.B.TFLS = 1;


}

void serial_write(const char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		while(!ASCLIN3_FLAGS.B.TFL);
		ASCLIN3_FLAGSCLEAR.B.TFLC = 1;

		ASCLIN3_TXDATA.B.DATA = str[i];
	}
}
