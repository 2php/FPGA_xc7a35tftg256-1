/*
 * delay.c
 *
 *  Created on: Sep 24, 2015
 *      Author: dong
 */
#include <stdio.h>
#include "xparameters.h"	/* XPAR parameters */
#include "xil_types.h"


void Delay_us(u16 us)	//100Mhz CLK...
{
	us = us*10;
	int i=0,j=0;
	for(i=0;i<us;i++)
		for(j=0;j<6;j++);
	//int i,j;
	//for (j=0;j  for (i=0;i<26;i++) asm("nop");
}
void Delay_ms(u16 ms)
{
	int i=0;
	int j=0;
	for(i=0;i<ms;i++)
		for(j=0;j<10;j++)
			Delay_us(100);
}


