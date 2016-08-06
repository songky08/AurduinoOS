/*
 * spi.c
 *
 *  Created on: 2016. 7. 22.
 *      Author: songky
 */
#include "bspconfig.h"
#include "spi.h"
#include <stdarg.h>
#include <string.h>
#include <machine/wdtcon.h>

#ifndef FALSE
#define FALSE	0
#endif /* FALSE */
#ifndef TRUE
#define TRUE	1
#endif /* TRUE */

#define is_digit(c)		((c >= '0') && (c <= '9'))

void serial_begin(int baud)
{
	/* Enables ASCLIN3 output */
	P15_IOCR4.B.PC7 = 0x12;
	P15_OUT.B.P7 = 0;

	/* sleep mode enable for config serial module */
	unlock_wdtcon();
	ASCLIN3_CLC.U = 0;
	lock_wdtcon();
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
	ASCLIN3_BRG.B.NUMERATOR = baud / 200;
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
int serial_write(char *fmt, ...)
{
	int ret, i;
	char buf[64];
	va_list ap;

	va_start(ap, fmt);
	ret = usr_vsprintf(buf, fmt, ap);
	va_end(ap);
	for (i = 0; buf[i]; i++)
	{
		ASCLIN3_TXDATA.B.DATA = buf[i];
		while (!ASCLIN3_FLAGS.B.TFL);
		ASCLIN3_FLAGSCLEAR.B.TFLC = 1;
	}

	return ret;
}

static int _cvt(unsigned long val, char *buf, long radix, char *digits)
{
	char temp[80];
	char *cp = temp;
	int length = 0;

	if (val == 0)
	{
		/* Special case */
		*cp++ = '0';
	}
	else
	{
		while (val)
		{
			*cp++ = digits[val % radix];
			val /= radix;
		}
	}
	while (cp != temp)
	{
		*buf++ = *--cp;
		length++;
	}
	*buf = '\0';
	return length;
}

int usr_vsprintf(char *dest, const char *fmt, va_list ap)
{
	char c, sign, *cp, *dp = dest;
	int left_prec, right_prec, zero_fill, length, pad, pad_on_right, i;
	char buf[32];
	long val;

	while ((c = *fmt++) != 0)
	{
		cp = buf;
		length = 0;
		if (c == '%')
		{
			c = *fmt++;
			left_prec = right_prec = pad_on_right = 0;
			if (c == '-')
			{
				c = *fmt++;
				pad_on_right++;
			}
			if (c == '0')
			{
				zero_fill = TRUE;
				c = *fmt++;
			}
			else
			{
				zero_fill = FALSE;
			}
			while (is_digit(c))
			{
				left_prec = (left_prec * 10) + (c - '0');
				c = *fmt++;
			}
			if (c == '.')
			{
				c = *fmt++;
				zero_fill++;
				while (is_digit(c))
				{
					right_prec = (right_prec * 10) + (c - '0');
					c = *fmt++;
				}
			}
			else
			{
				right_prec = left_prec;
			}
			sign = '\0';
			/* handle type modifier */
			if (c == 'l' || c == 'h')
			{
				c = *fmt++;
			}
			switch (c)
			{
				case 'd' :
				case 'u' :
				case 'x' :
				case 'X' :
					val = va_arg(ap, long);
					switch (c)
					{
						case 'd' :
							if (val < 0)
							{
								sign = '-';
								val = -val;
							}
							/* fall through */
						case 'u' :
							length = _cvt(val, buf, 10, "0123456789");
							break;
						case 'x' :
							length = _cvt(val, buf, 16, "0123456789abcdef");
							break;
						case 'X' :
							length = _cvt(val, buf, 16, "0123456789ABCDEF");
							break;
					}
					break;
				case 's' :
					cp = va_arg(ap, char *);
					length = strlen(cp);
					break;
				case 'c' :
					c = (char)va_arg(ap, long);
					*dp++ = c;
					continue;
				default:
					*dp++ = '?';
			}
			pad = left_prec - length;
			if (sign != '\0')
			{
				pad--;
			}
			if (zero_fill)
			{
				c = '0';
				if (sign != '\0')
				{
					*dp++ = sign;
					sign = '\0';
				}
			}
			else
			{
				c = ' ';
			}
			if (!pad_on_right)
			{
				while (pad-- > 0)
				{
					*dp++ = c;
				}
			}
			if (sign != '\0')
			{
				*dp++ = sign;
			}
			while (length-- > 0)
			{
				c = *cp++;
				if (c == '\n')
				{
					*dp++ = '\r';
				}
				*dp++ = c;
			}
			if (pad_on_right)
			{
				while (pad-- > 0)
				{
					*dp++= ' ';
				}
			}
		}
		else
		{
			if (c == '\n')
			{
				*dp++= '\r';
			}
			*dp++ = c;
		}
	}

	*dp = '\0';

	return ((int)dp - (int)dest);
}
