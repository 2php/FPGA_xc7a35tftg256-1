/*
 * ctiic.h
 *
 *  Created on: Jul 8, 2016
 *      Author: wxd
 */

#ifndef CTIIC_H_
#define CTIIC_H_

#include "xil_types.h"
#include <xgpio.h>
XGpio touch_scl;
XGpio touch_sda;
XGpio touch_rst;
XGpio touch_intc;

void CT_SDA_OUT();
void CT_SDA_IN();
void CT_IIC_Init(void);
void CT_IIC_Start(void);
void CT_IIC_Stop(void);
void CT_IIC_Send_Byte(u8 txd);
u8 CT_IIC_Read_Byte(unsigned char ack);
u8 CT_IIC_Wait_Ack(void);
void CT_IIC_Ack(void);
void CT_IIC_NAck(void);

#endif /* CTIIC_H_ */
