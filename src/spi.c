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
	/* Enables ASCLIN3output */
	P15_IOCR4.B.PC7 = 0x12;
	P15_OUT.B.P7 = 0;

	/* sleep mode enable for config serial module */
	ASCLIN3_CLC.U = 0;
	/* read back for activating module */
	ASCLIN3_CLC.U;
	/* select ARX0B/P15.3 as input pin */
	ASCLIN3_IOCR.B.ALTI = 1;
	/* loop back mode is disabled */
	ASCLIN3_IOCR.B.LB = 0;
	/* Disables clock */
	ASCLIN3_CSR.U = 0;
	/* Defines the number of bytes written to the Tx FIFO with one FPI bus write */
	ASCLIN3_TXFIFOCON.B.INW = 1;
	/* Enables the TxFIFO outlet */
	ASCLIN3_TXFIFOCON.B.ENO = 1;
	/* Write of 1 brings the Tx FIFO in empty state */
	ASCLIN3_TXFIFOCON.B.FLUSH = 1;
	/* Defines the number of bytes read to the Rx FIFO with one FPI bus read */
	ASCLIN3_RXFIFOCON.B.OUTW = 1;
	/* Enables the receiver and the filling of the Rx FIFO through the shift register */
	ASCLIN3_RXFIFOCON.B.ENI = 1;
	/* Write of 1 brings the Rx FIFO in empty state */
	ASCLIN3_RXFIFOCON.B.FLUSH = 1;
	/* Baud rate fomular : (fa * numerator) / ((prescaler + 1) * (oversampling + 1) * denominator) */
	ASCLIN3_BITCON.B.PRESCALER = 9;
	ASCLIN3_BITCON.B.OVERSAMPLING = 0xF;
	ASCLIN3_BRG.B.DENOMINATOR = 3125;
	ASCLIN3_BRG.B.NUMERATOR = baud / 100;
	/* sample point is recommended about half of oversampling*/
	ASCLIN3_BITCON.B.SAMPLEPOINT = 8;
	/* Defines numbers of stop bit*/
	ASCLIN3_FRAMECON.B.STOP = 1;
	/* Defines numbers of lead bit*/
	ASCLIN3_FRAMECON.B.LEAD = 1;
	/* Enables initial mode before SPI mode */
	ASCLIN3_FRAMECON.B.MODE = 0;
	/* no parity mode */
	ASCLIN3_FRAMECON.B.PEN = 0;
	/* Enables LSB first */
	ASCLIN3_FRAMECON.B.MSB = 0;
	/* Defines data length is 8 (DATLEN + 1) */
	ASCLIN3_DATCON.B.DATLEN = 7;
	/* Enables SPI mode and synchronous mode */
	ASCLIN3_FRAMECON.B.MODE = 2;
	/* use fclc clock */
	ASCLIN3_CSR.B.CLKSEL = 1;
	/* Defines interrupt flags */
	ASCLIN3_FLAGSENABLE.B.TFLE = 1;


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

