#ifndef __TOUCH_H__
#define __TOUCH_H__


#include "gt9147.h"
#include <xgpio.h>
extern u16 POINT_COLOR;
extern u8 CMD_RDX;
extern u8 CMD_RDY;
extern XGpio touch_scl;
extern XGpio touch_sda;
extern XGpio touch_rst;
extern XGpio touch_intc;

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����������(֧��ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A/GT9147/FT5206��)����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/25
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved						 
//////////////////////////////////////////////////////////////////////////////////


#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);		//������У׼ 
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//������оƬ��������	   

   
////����������
//void TP_Write_Byte(u8 num);						//�����оƬд��һ������
//u16 TP_Read_AD(u8 CMD);							//��ȡADת��ֵ
//u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
//u8 TP_Read_XY(u16 *x,u16 *y);					//˫�����ȡ(X+Y)
//u8 TP_Read_XY2(u16 *x,u16 *y);					//����ǿ�˲���˫���������ȡ
//void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//��һ������У׼��
//void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//��һ�����
//void TP_Save_Adjdata(void);						//����У׼����
//u8 TP_Get_Adjdata(void);						//��ȡУ׼����
//void TP_Adjust(void);							//������У׼
//void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//��ʾУ׼��Ϣ
//������/������ ���ú���
u8 TP_Scan(u8 tp);								//ɨ��
u8 TP_Init(void);								//��ʼ��
void Load_Drow_Dialog(void);
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
u16 my_abs(u16 x1,u16 x2);
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);
void ctp_test(void);
#endif

















