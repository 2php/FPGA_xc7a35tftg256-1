/*
 * otta2001.h
 *
 *  Created on: Jul 8, 2016
 *      Author: wxd
 */

#ifndef __OTT2001A_H
#define __OTT2001A_H


#include "xil_types.h"



#define GT_CMD_WR 		0X28
#define GT_CMD_RD 		0X29


#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40
#define CT_MAX_TOUCH  5



//extern _m_tp_dev tp_dev;

#define GT_CTRL_REG 	0X8040
#define GT_CFGS_REG 	0X8047
#define GT_CHECK_REG 	0X80FF
#define GT_PID_REG 		0X8140

#define GT_GSTID_REG 	0X814E
#define GT_TP1_REG 		0X8150
#define GT_TP2_REG 		0X8158
#define GT_TP3_REG 		0X8160
#define GT_TP4_REG 		0X8168
#define GT_TP5_REG 		0X8170


u8 GT9147_Send_Cfg(u8 mode);
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len);
void GT9147_Init(void);
u8 GT9147_Scan(u8);

#endif
