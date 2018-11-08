#include "touch.h" 
#include "/mnt/sdb1/Project/FPGA2018/caulator_2018/caulator_2018.sdk/mbtest/src/display/LCD.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include <xparameters.h>
#include <xgpio.h>
#include "gt9147.h"
#include "ctiic.h"


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
extern u8 CMD_RDX;
extern u8 CMD_RDY;

 const u16 POINT_COLOR_TBL[5]={RED,GREEN,BLUE,BROWN,GRED};
_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
//	TP_Adjust,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//Ĭ��Ϊtouchtype=0������.

 	 			    					   
//SPIд����
//������ICд��1byte����    
//num:Ҫд�������
void TP_Write_Byte(u8 num)
{
	u8 count=0;
	for(count=0;count<8;count++)
	{
		if(num&0x80)XGpio_DiscreteWrite(&touch_sda, 1, 1);
		else XGpio_DiscreteWrite(&touch_sda, 1,0);
		num<<=1;
		XGpio_DiscreteWrite(&touch_scl, 1, 0);
		delay_us(1);
		XGpio_DiscreteWrite(&touch_scl, 1, 1);		//��������Ч
	}
}
//SPI������ 
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������	   
u16 TP_Read_AD(u8 CMD)
{
	u8 count=0;
	u16 Num=0;

	XGpio_DiscreteWrite(&touch_scl, 1, 0);		//������ʱ��
	XGpio_DiscreteWrite(&touch_sda, 1, 0); 	//����������
	XGpio_DiscreteWrite(&touch_rst, 1, 0);		//ѡ�д�����IC
	TP_Write_Byte(CMD);//����������
	delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
	XGpio_DiscreteWrite(&touch_scl, 1, 0);
	delay_us(1);
	XGpio_DiscreteWrite(&touch_scl, 1, 1);		//��1��ʱ�ӣ����BUSY
	delay_us(1);
	XGpio_DiscreteWrite(&touch_scl, 1, 0);
	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч
	{
		Num<<=1;
		XGpio_DiscreteWrite(&touch_scl, 1, 0);	//�½�����Ч
		delay_us(1);
		XGpio_DiscreteWrite(&touch_scl, 1, 1);

	}
	Num>>=4;   	//ֻ�и�12λ��Ч.
	XGpio_DiscreteWrite(&touch_rst, 1, 1);		//�ͷ�Ƭѡ
	return(Num);
}
//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;
}
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);
	if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}
//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.	   
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
u8 TP_Read_XY2(u16 *x,u16 *y)
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;
    flag=TP_Read_XY(&x1,&y1);
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);
    if(flag==0)return(0);
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;
}
//////////////////////////////////////////////////////////////////////////////////		  
//��LCD�����йصĺ���  
//��һ��������
//����У׼�õ�
//x,y:����
//color:��ɫ
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color)
{
	POINT_COLOR=color;
	LCD_DrawLine(x-12,y,x+13,y);//����
	LCD_DrawLine(x,y-12,x,y+13);//����
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);
	LCD_Draw_Circle(x,y,6);//������Ȧ
}	  
//��һ�����(2*2�ĵ�)		   
//x,y:����
//color:��ɫ
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	POINT_COLOR=color;
	LCD_DrawPoint(x,y);//���ĵ� 
	LCD_DrawPoint(x+1,y);
	LCD_DrawPoint(x,y+1);
	LCD_DrawPoint(x+1,y+1);	 	  	
}						  
//////////////////////////////////////////////////////////////////////////////////		  
//��������ɨ��
//tp:0,��Ļ����;1,��������(У׼�����ⳡ����)
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 TP_Scan(u8 tp)
{

	u8 a=GT9147_Scan(0);
	if(a)//�а�������
	{
//		if(tp)TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//��ȡ��������
//		else if(TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]))//��ȡ��Ļ����
//		{
//	 		tp_dev.x[0]=tp_dev.xfac*tp_dev.x[0]+tp_dev.xoff;//�����ת��Ϊ��Ļ����
//			tp_dev.y[0]=tp_dev.yfac*tp_dev.y[0]+tp_dev.yoff;
//	 	}
		if((tp_dev.sta&TP_PRES_DOWN)==0)//֮ǰû�б�����
		{		 
			tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//��������  
			tp_dev.x[4]=tp_dev.x[0];//��¼��һ�ΰ���ʱ������
			tp_dev.y[4]=tp_dev.y[0];  	   			 
		}			   
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);//��ǰ����ɿ�	
		}else//֮ǰ��û�б�����
		{
			tp_dev.x[4]=0;
			tp_dev.y[4]=0;
//			tp_dev.x[0]=0xffff;
//			tp_dev.y[0]=0xffff;
		}	    
	}
	return tp_dev.sta&TP_PRES_DOWN;//���ص�ǰ�Ĵ���״̬
}	  
//////////////////////////////////////////////////////////////////////////	 
//������EEPROM����ĵ�ַ�����ַ,ռ��13���ֽ�(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
#define SAVE_ADDR_BASE 40
//����У׼����										    
//void TP_Save_Adjdata(void)
//{
//	s32 temp;
//	//����У�����!
//	temp=tp_dev.xfac*100000000;//����xУ������
//    AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);
//	temp=tp_dev.yfac*100000000;//����yУ������
//    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);
//	//����xƫ����
//    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);
//	//����yƫ����
//	AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);
//	//���津������
//	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);
//	temp=0X0A;//���У׼����
//	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp);
//}
//�õ�������EEPROM�����У׼ֵ
//����ֵ��1���ɹ���ȡ����
//        0����ȡʧ�ܣ�Ҫ����У׼
//u8 TP_Get_Adjdata(void)
//{
//	s32 tempfac;
//	tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);//��ȡ�����,���Ƿ�У׼����
//	if(tempfac==0X0A)//�������Ѿ�У׼����
//	{
//		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);
//		tp_dev.xfac=(float)tempfac/100000000;//�õ�xУ׼����
//		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);
//		tp_dev.yfac=(float)tempfac/100000000;//�õ�yУ׼����
//	    //�õ�xƫ����
//		tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);
// 	    //�õ�yƫ����
//		tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);
// 		tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);//��ȡ�������ͱ��
//		if(tp_dev.touchtype)//X,Y��������Ļ�෴
//		{
//			CMD_RDX=0X90;
//			CMD_RDY=0XD0;
//		}else				   //X,Y��������Ļ��ͬ
//		{
//			CMD_RDX=0XD0;
//			CMD_RDY=0X90;
//		}
//		return 1;
//	}
//	return 0;
//}
//��ʾ�ַ���
u8* const TP_REMIND_MSG_TBL="Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";
 					  
//��ʾУ׼���(��������)
//void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
//{
//	POINT_COLOR=RED;
//	LCD_ShowString(40,160,lcddev.width,lcddev.height,16,"x1:");
// 	LCD_ShowString(40+80,160,lcddev.width,lcddev.height,16,"y1:");
// 	LCD_ShowString(40,180,lcddev.width,lcddev.height,16,"x2:");
// 	LCD_ShowString(40+80,180,lcddev.width,lcddev.height,16,"y2:");
//	LCD_ShowString(40,200,lcddev.width,lcddev.height,16,"x3:");
// 	LCD_ShowString(40+80,200,lcddev.width,lcddev.height,16,"y3:");
//	LCD_ShowString(40,220,lcddev.width,lcddev.height,16,"x4:");
// 	LCD_ShowString(40+80,220,lcddev.width,lcddev.height,16,"y4:");
// 	LCD_ShowString(40,240,lcddev.width,lcddev.height,16,"fac is:");
//	LCD_ShowNum(40+24,160,x0,4,16);		//��ʾ��ֵ
//	LCD_ShowNum(40+24+80,160,y0,4,16);	//��ʾ��ֵ
//	LCD_ShowNum(40+24,180,x1,4,16);		//��ʾ��ֵ
//	LCD_ShowNum(40+24+80,180,y1,4,16);	//��ʾ��ֵ
//	LCD_ShowNum(40+24,200,x2,4,16);		//��ʾ��ֵ
//	LCD_ShowNum(40+24+80,200,y2,4,16);	//��ʾ��ֵ
//	LCD_ShowNum(40+24,220,x3,4,16);		//��ʾ��ֵ
//	LCD_ShowNum(40+24+80,220,y3,4,16);	//��ʾ��ֵ
// 	LCD_ShowNum(40+56,240,fac,3,16); 	//��ʾ��ֵ,����ֵ������95~105��Χ֮��.
//
//}
		 
//������У׼����
//�õ��ĸ�У׼����
void TP_Adjust(void){}
//{
//	u16 pos_temp[4][2];//���껺��ֵ
//	u8  cnt=0;
//	u16 d1,d2;
//	u32 tem1,tem2;
//	double fac;
//	u16 outtime=0;
// 	cnt=0;
//	POINT_COLOR=BLUE;
//	BACK_COLOR =WHITE;
//	LCD_Clear(WHITE);//����
//	POINT_COLOR=RED;//��ɫ
//	LCD_Clear(WHITE);//����
//	POINT_COLOR=BLACK;
//	LCD_ShowString(40,40,160,100,16,(u8*)TP_REMIND_MSG_TBL);//��ʾ��ʾ��Ϣ
//	TP_Drow_Touch_Point(20,20,RED);//����1
//	tp_dev.sta=0;//���������ź�
//	tp_dev.xfac=0;//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������
//	while(1)//�������10����û�а���,���Զ��˳�
//	{
////		GT9147_Scan();//ɨ����������
//		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//����������һ��(��ʱ�����ɿ���.)
//		{
//			outtime=0;
//			tp_dev.sta&=~(1<<6);//��ǰ����Ѿ����������.
//
//			pos_temp[cnt][0]=tp_dev.x[0];
//			pos_temp[cnt][1]=tp_dev.y[0];
//			cnt++;
//			switch(cnt)
//			{
//				case 1:
//					TP_Drow_Touch_Point(20,20,WHITE);				//�����1
//					TP_Drow_Touch_Point(lcddev.width-20,20,RED);	//����2
//					break;
//				case 2:
// 					TP_Drow_Touch_Point(lcddev.width-20,20,WHITE);	//�����2
//					TP_Drow_Touch_Point(20,lcddev.height-20,RED);	//����3
//					break;
//				case 3:
// 					TP_Drow_Touch_Point(20,lcddev.height-20,WHITE);			//�����3
// 					TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,RED);	//����4
//					break;
//				case 4:	 //ȫ���ĸ����Ѿ��õ�
//	    		    //�Ա����
//					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
//					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
//					tem1*=tem1;
//					tem2*=tem2;
//					d1=sqrt(tem1+tem2);//�õ�1,2�ľ���
//
//					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
//					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
//					tem1*=tem1;
//					tem2*=tem2;
//					d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
//					fac=(float)d1/d2;
//					if(fac<0.95||fac>1.05||d1==0||d2==0)//���ϸ�
//					{
//						cnt=0;
// 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
//   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
// 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
// 						continue;
//					}
//					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
//					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
//					tem1*=tem1;
//					tem2*=tem2;
//					d1=sqrt(tem1+tem2);//�õ�1,3�ľ���
//
//					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
//					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
//					tem1*=tem1;
//					tem2*=tem2;
//					d2=sqrt(tem1+tem2);//�õ�2,4�ľ���
//					fac=(float)d1/d2;
//					if(fac<0.95||fac>1.05)//���ϸ�
//					{
//						cnt=0;
// 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
//   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
// 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
//						continue;
//					}//��ȷ��
//
//					//�Խ������
//					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
//					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
//					tem1*=tem1;
//					tem2*=tem2;
//					d1=sqrt(tem1+tem2);//�õ�1,4�ľ���
//
//					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
//					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
//					tem1*=tem1;
//					tem2*=tem2;
//					d2=sqrt(tem1+tem2);//�õ�2,3�ľ���
//					fac=(float)d1/d2;
//					if(fac<0.95||fac>1.05)//���ϸ�
//					{
//						cnt=0;
// 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
//   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
// 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
//						continue;
//					}//��ȷ��
//					//������
//					tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//�õ�xfac
//					tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//�õ�xoff
//
//					tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//�õ�yfac
//					tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//�õ�yoff
//					if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)//������Ԥ����෴��.
//					{
//						cnt=0;
// 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
//   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
//						LCD_ShowString(40,26,lcddev.width,lcddev.height,16,"TP Need readjust!");
//						tp_dev.touchtype=!tp_dev.touchtype;//�޸Ĵ�������.
//						if(tp_dev.touchtype)//X,Y��������Ļ�෴
//						{
//							CMD_RDX=0X90;
//							CMD_RDY=0XD0;
//						}else				   //X,Y��������Ļ��ͬ
//						{
//							CMD_RDX=0XD0;
//							CMD_RDY=0X90;
//						}
//						continue;
//					}
//					POINT_COLOR=BLUE;
//					LCD_Clear(WHITE);//����
//					LCD_ShowString(35,110,lcddev.width,lcddev.height,16,"Touch Screen Adjust OK!");//У�����
//					delay_ms(1000);
////					TP_Save_Adjdata();
// 					LCD_Clear(WHITE);//����
//					return;//У�����
//			}
//		}
//		delay_ms(10);
//		outtime++;
//		if(outtime>1000)
//		{
//			TP_Get_Adjdata();
//			break;
//	 	}
// 	}
//}
//��������ʼ��  		    
//����ֵ:0,û�н���У׼
//       1,���й�У׼
u8 TP_Init(void)
{	
//	if(lcddev.id==0X5510)				//4.3����ݴ�����
//	{
	GT9147_Init();
				//��GT9147

		tp_dev.scan=GT9147_Scan;	//ɨ�躯��ָ��GT9147������ɨ��

//		else
//		{
//			OTT2001A_Init();
//			tp_dev.scan=OTT2001A_Scan;	//ɨ�躯��ָ��OTT2001A������ɨ��
//		}
		tp_dev.touchtype|=0X80;			//������ 
		tp_dev.touchtype|=lcddev.dir&0X01;//������������ 
		return 0;
//	}
//	else if(lcddev.id==0X1963)			//7����ݴ�����
//	{
//		FT5206_Init();
//		tp_dev.scan=FT5206_Scan;		//ɨ�躯��ָ��GT9147������ɨ��
//		tp_dev.touchtype|=0X80;			//������
//		tp_dev.touchtype|=lcddev.dir&0X01;//������������
//		return 0;
//	}else
//	{
		//ע��,ʱ��ʹ��֮��,��GPIO�Ĳ�������Ч
		//��������֮ǰ,����ʹ��ʱ��.����ʵ���������������
//		RCC->APB2ENR|=1<<4;    //PCʱ��ʹ��
//		RCC->APB2ENR|=1<<0;    //��������ʱ��
//		GPIOC->CRL&=0XFFFF0000;//PC0~3
//		GPIOC->CRL|=0X00003883;
//		GPIOC->CRH&=0XFF0FFFFF;//PC13
//		GPIOC->CRH|=0X00300000;//PC13�������
//		GPIOC->ODR|=0X200f;    //PC0~3 13 ȫ������
//
//		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//��һ�ζ�ȡ��ʼ��
//		AT24CXX_Init();		//��ʼ��24CXX
//		if(TP_Get_Adjdata())return 0;//�Ѿ�У׼
//		else			   //δУ׼?
//		{
//			LCD_Clear(WHITE);//����
//			TP_Adjust();  	//��ĻУ׼
//			TP_Save_Adjdata();
//		}
//		TP_Get_Adjdata();
//	}
//	return 1;
}

void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//ÇåÆÁ
 	POINT_COLOR=BLUE;//ÉèÖÃ×ÖÌåÎªÀ¶É«
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//ÏÔÊ¾ÇåÆÁÇøÓò
  	POINT_COLOR=RED;//ÉèÖÃ»­±ÊÀ¶É«
}
////////////////////////////////////////////////////////////////////////////////

void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);
}


void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++)
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside
		{
 			if (x>imax)
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}

u16 my_abs(u16 x1,u16 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}


void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	if(x1<size|| x2<size||y1<size|| y2<size)return;
	delta_x=x2-x1; //¼ÆËã×ø±êÔöÁ¿
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //ÉèÖÃµ¥²½·½Ïò
	else if(delta_x==0)incx=0;//´¹Ö±Ïß
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//Ë®Æ½Ïß
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //Ñ¡È¡»ù±¾ÔöÁ¿×ø±êÖá
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//»­ÏßÊä³ö
	{
		gui_fill_circle(uRow,uCol,size,color);//»­µã
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


void ctp_test(void)
{
	u8 t=0;
	u8 i=0;
 	u16 lastpos[5][2];		//
	while(1)
	{

		TP_Scan(0);
		for(t=0;t<CT_MAX_TOUCH;t++)//
		{
			if((tp_dev.sta)&(1<<t))//
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)//
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<16)
					{
						Load_Drow_Dialog();//
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}

//		delay_ms(5);i++;
//		if(i%20==0)LED0=!LED0;
	}
}
