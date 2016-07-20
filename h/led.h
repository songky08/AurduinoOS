/*
 * led.h
 *
 *      Author: songky08@gmail.com
 */

#ifndef LED_H_
#define LED_H_

#include "bspconfig.h"

void pinMode (int pin, int mode)
{
	if (pin < MAX_LED)
	{
		switch (pin)
		{
		case 0:
			P15_IOCR0.B.PC3 = mode;	//digital pin 0
			break;
		case 1:
			P15_IOCR0.B.PC2 = mode;	//digital pin 1
			break;
		case 2:
			P02_IOCR0.B.PC0 = mode;	//digital pin 2
			break;
		case 3:
			P02_IOCR0.B.PC1 = mode;	//digital pin 3
			break;
		case 4:
			P10_IOCR4.B.PC4 = mode;	//digital pin 4
			break;
		case 5:
			P02_IOCR0.B.PC3 = mode;	//digital pin 5
			break;
		case 6:
			P02_IOCR4.B.PC4 = mode;	//digital pin 6
			break;
		case 7:
			P02_IOCR4.B.PC5 = mode;	//digital pin 7
			break;
		case 8:
			P02_IOCR4.B.PC6 = mode;	//digital pin 8
			break;
		case 9:
			P02_IOCR4.B.PC7 = mode;	//digital pin 9
			break;
		case 10:
			P10_IOCR4.B.PC5 = mode;	//digital pin 10
			break;
		case 11:
			P10_IOCR0.B.PC3 = mode;	//digital pin 11
			break;
		case 12:
			P10_IOCR0.B.PC1 = mode;	//digital pin 12
			break;
		case 13:
			P10_IOCR0.B.PC2 = mode;	//digital pin 13
			break;
		case 14:
			P15_IOCR0.B.PC0 = mode;	//digital pin 14
			break;
		case 15:
			P15_IOCR0.B.PC1 = mode;	//digital pin 15
			break;
		case 16:
			P33_IOCR8.B.PC9 = mode;	//digital pin 16
			break;
		case 17:
			P33_IOCR8.B.PC8 = mode;	//digital pin 17
			break;
		case 18:
			P20_IOCR0.B.PC0 = mode;	//digital pin 18
			break;
		case 19:
			P20_IOCR0.B.PC3 = mode;	//digital pin 19
			break;
		case 20:
			P15_IOCR4.B.PC5 = mode;	//digital pin 20
			break;
		case 21:
			P15_IOCR4.B.PC4 = mode;	//digital pin 21
			break;
		case 22:
			P14_IOCR0.B.PC0 = mode;	//digital pin 22
			break;
		case 23:
			P14_IOCR0.B.PC1 = mode;	//digital pin 23
			break;
		case 24:
			P15_IOCR4.B.PC6 = mode;	//digital pin 24
			break;
		case 25:
			P00_IOCR0.B.PC0 = mode;	//digital pin 25
			break;
		case 26:
			P00_IOCR8.B.PC8 = mode;	//digital pin 26
			break;
		case 27:
			P00_IOCR0.B.PC1 = mode;	//digital pin 27
			break;
		case 28:
			P00_IOCR8.B.PC9 = mode;	//digital pin 28
			break;
		case 29:
			P00_IOCR0.B.PC2 = mode;	//digital pin 29
			break;
		case 30:
			P00_IOCR8.B.PC10 = mode;//digital pin 30
			break;
		case 31:
			P00_IOCR0.B.PC3 = mode;	//digital pin 31
			break;
		case 32:
			P00_IOCR8.B.PC11 = mode;//digital pin 32
			break;
		case 33:
			P00_IOCR4.B.PC4 = mode;	//digital pin 33
			break;
		case 34:
			P00_IOCR12.B.PC12 = mode;//digital pin 34
			break;
		case 35:
			P00_IOCR4.B.PC5 = mode;	//digital pin 35
			break;
		case 36:
			P33_IOCR0.B.PC2 = mode;	//digital pin 36
			break;
		case 37:
			P00_IOCR4.B.PC6 = mode;	//digital pin 37
			break;
		case 38:
			P33_IOCR0.B.PC1 = mode;	//digital pin 38
			break;
		case 39:
			P00_IOCR4.B.PC7 = mode;	//digital pin 39
			break;
		case 40:
			P33_IOCR0.B.PC0 = mode;	//digital pin 40
			break;
		case 41:
			P11_IOCR8.B.PC9 = mode;	//digital pin 41
			break;
		case 42:
			P11_IOCR8.B.PC10 = mode;//digital pin 42
			break;
		case 43:
			P11_IOCR8.B.PC11 = mode;//digital pin 43
			break;
		case 44:
			P33_IOCR0.B.PC3 = mode;	//digital pin 44
			break;
		case 45:
			P11_IOCR0.B.PC2 = mode;	//digital pin 45
			break;
		case 46:
			P11_IOCR0.B.PC3 = mode;	//digital pin 46
			break;
		case 47:
			P11_IOCR4.B.PC6 = mode;	//digital pin 47
			break;
		case 48:
			P21_IOCR0.B.PC3 = mode;	//digital pin 48 (B-step)
			break;
		case 49:
			P21_IOCR0.B.PC0 = mode;	//digital pin 49
			break;
		case 50:
			P21_IOCR0.B.PC3 = mode;	//digital pin 50
			break;
		case 51:
			P02_IOCR8.B.PC8 = mode;	//digital pin 51
			break;
		case 52:
			P15_IOCR8.B.PC8 = mode;	//digital pin 52
			break;
		case 53:
			P11_IOCR12.B.PC12 = mode;//digital pin 53
			break;
		}
	}
}
void digitalWrite(int pin, int sig)
{
	if(pin < MAX_LED)
	{
		switch (pin)
		{
		case 0:
			P15_OUT.B.P3 = sig;	//digital pin 0
			break;
		case 1:
			P15_OUT.B.P2 = sig;	//digital pin 1
			break;
		case 2:
			P02_OUT.B.P0 = sig;	//digital pin 2
			break;
		case 3:
			P02_OUT.B.P1 = sig;	//digital pin 3
			break;
		case 4:
			P10_OUT.B.P4 = sig;	//digital pin 4
			break;
		case 5:
			P02_OUT.B.P3 = sig;	//digital pin 5
			break;
		case 6:
			P02_OUT.B.P4 = sig;	//digital pin 6
			break;
		case 7:
			P02_OUT.B.P5 = sig;	//digital pin 7
			break;
		case 8:
			P02_OUT.B.P6 = sig;	//digital pin 8
			break;
		case 9:
			P02_OUT.B.P7 = sig;	//digital pin 9
			break;
		case 10:
			P10_OUT.B.P5 = sig;	//digital pin 10
			break;
		case 11:
			P10_OUT.B.P3 = sig;	//digital pin 11
			break;
		case 12:
			P10_OUT.B.P1 = sig;	//digital pin 12
			break;
		case 13:
			P10_OUT.B.P2 = sig;	//digital pin 13
			break;
		case 14:
			P15_OUT.B.P0 = sig;	//digital pin 14
			break;
		case 15:
			P15_OUT.B.P1 = sig;	//digital pin 15
			break;
		case 16:
			P33_OUT.B.P9 = sig;	//digital pin 16
			break;
		case 17:
			P33_OUT.B.P8 = sig;	//digital pin 17
			break;
		case 18:
			P20_OUT.B.P0 = sig;	//digital pin 18
			break;
		case 19:
			P20_OUT.B.P3 = sig;	//digital pin 19
			break;
		case 20:
			P15_OUT.B.P5 = sig;	//digital pin 20
			break;
		case 21:
			P15_OUT.B.P4 = sig;	//digital pin 21
			break;
		case 22:
			P14_OUT.B.P0 = sig;	//digital pin 22
			break;
		case 23:
			P14_OUT.B.P1 = sig;	//digital pin 23
			break;
		case 24:
			P15_OUT.B.P6 = sig;	//digital pin 24
			break;
		case 25:
			P00_OUT.B.P0 = sig;	//digital pin 25
			break;
		case 26:
			P00_OUT.B.P8 = sig;	//digital pin 26
			break;
		case 27:
			P00_OUT.B.P1 = sig;	//digital pin 27
			break;
		case 28:
			P00_OUT.B.P9 = sig;	//digital pin 28
			break;
		case 29:
			P00_OUT.B.P2 = sig;	//digital pin 29
			break;
		case 30:
			P00_OUT.B.P10 = sig;//digital pin 30
			break;
		case 31:
			P00_OUT.B.P3 = sig;	//digital pin 31
			break;
		case 32:
			P00_OUT.B.P11 = sig;//digital pin 32
			break;
		case 33:
			P00_OUT.B.P4 = sig;	//digital pin 33
			break;
		case 34:
			P00_OUT.B.P12 = sig;//digital pin 34
			break;
		case 35:
			P00_OUT.B.P5 = sig;	//digital pin 35
			break;
		case 36:
			P33_OUT.B.P2 = sig;	//digital pin 36
			break;
		case 37:
			P00_OUT.B.P6 = sig;	//digital pin 37
			break;
		case 38:
			P33_OUT.B.P1 = sig;	//digital pin 38
			break;
		case 39:
			P00_OUT.B.P7 = sig;	//digital pin 39
			break;
		case 40:
			P33_OUT.B.P0 = sig;	//digital pin 40
			break;
		case 41:
			P11_OUT.B.P9 = sig;	//digital pin 41
			break;
		case 42:
			P11_OUT.B.P10 = sig;//digital pin 42
			break;
		case 43:
			P11_OUT.B.P11 = sig;//digital pin 43
			break;
		case 44:
			P33_OUT.B.P3 = sig;	//digital pin 44
			break;
		case 45:
			P11_OUT.B.P2 = sig;	//digital pin 45
			break;
		case 46:
			P11_OUT.B.P3 = sig;	//digital pin 46
			break;
		case 47:
			P11_OUT.B.P6 = sig;	//digital pin 47
			break;
		case 48:
			P21_OUT.B.P3 = sig;	//digital pin 48 (B-step)
			break;
		case 49:
			P21_OUT.B.P0 = sig;	//digital pin 49
			break;
		case 50:
			P21_OUT.B.P3 = sig;	//digital pin 50
			break;
		case 51:
			P02_OUT.B.P8 = sig;	//digital pin 51
			break;
		case 52:
			P15_OUT.B.P8 = sig;	//digital pin 52
			break;
		case 53:
			P11_OUT.B.P12 = sig;//digital pin 53
			break;
		}
	}
}

#endif /* LED_H_ */
