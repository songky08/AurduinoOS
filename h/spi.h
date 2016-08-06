/*
 * spi.h
 *
 *  Created on: 2016. 7. 22.
 *      Author: songky08@gmail.com
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdarg.h>

void serial_begin(int baud);
int serial_write(char *fmt, ...);
static int _cvt(unsigned long val, char *buf, long radix, char *digits);
int usr_vsprintf(char *dest, const char *fmt, va_list ap);


#endif /* SPI_H_ */
