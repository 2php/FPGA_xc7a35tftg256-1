/*
 * ctiic.c
 *
 *  Created on: Jul 8, 2016
 *      Author: wxd
 */
#include "xparameters.h"	/* XPAR parameters */
#include <xgpio.h>
#include "ctiic.h"
#include "delay.h"


extern XGpio touch_scl;
extern XGpio touch_sda;
extern XGpio touch_rst;
extern XGpio touch_intc;
//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	Delay_us(2);
}
//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{
	XGpio_Initialize (&touch_scl, XPAR_HIER_PERIPH_HIER_LCD_TOUCH_GPIO_CLK_DEVICE_ID);		//scl
	XGpio_Initialize (&touch_sda, XPAR_HIER_PERIPH_HIER_LCD_TOUCH_GPIO_SDA_DEVICE_ID);		//touch_sda
	XGpio_Initialize (&touch_rst, XPAR_HIER_PERIPH_HIER_LCD_TOUCH_GPIO_TCS_DEVICE_ID);		//rst
	XGpio_Initialize (&touch_intc, XPAR_HIER_PERIPH_HIER_LCD_TOUCH_GPIO_INT_DEVICE_ID);//intc
	XGpio_SetDataDirection(&touch_intc , 1 , 0);
	XGpio_SetDataDirection(&touch_scl , 1 , 0);
	XGpio_SetDataDirection(&touch_sda , 1 , 0);
	XGpio_SetDataDirection(&touch_rst , 1 , 0);
	XGpio_DiscreteWrite(&touch_sda, 1, 1);					//CT_IIC_SDA=1;
	XGpio_DiscreteWrite(&touch_scl, 1, 1);
//	XGpio_SetDataDirection(&touch_scl, 1, 0);
//
//	XGpio_SetDataDirection(&touch_rst, 1, 0);
//
//	XGpio_SetDataDirection(&touch_intc, 1, 0);
}

void CT_SDA_OUT()
{
	XGpio_SetDataDirection(&touch_sda , 1 , 0);						//touch_sda output
}
void CT_SDA_IN()
{
	XGpio_SetDataDirection(&touch_sda , 1 , 1);						//touch_sda input
}

//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     									//touch_sda�����
	XGpio_DiscreteWrite(&touch_sda, 1, 1);					//CT_IIC_SDA=1;
	XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
	Delay_us(30);
	XGpio_DiscreteWrite(&touch_sda, 1, 0);					//CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	CT_Delay();
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//touch_sda�����
	XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
	Delay_us(30);
	XGpio_DiscreteWrite(&touch_sda, 1, 0);					//CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	XGpio_DiscreteWrite(&touch_sda, 1, 1);					//CT_IIC_SDA=1;//����I2C���߽����ź�
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
	CT_SDA_IN();//SDA����Ϊ���
	u32 read = 0;
	read = XGpio_DiscreteRead(&touch_sda, 1);
	while(read)
	{
		read = XGpio_DiscreteRead(&touch_sda, 1);
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		}
		CT_Delay();
	}
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;//ʱ�����0
	return 0;
}
//����ACKӦ��
void CT_IIC_Ack(void)
{
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	XGpio_DiscreteWrite(&touch_sda, 1, 0);					//CT_IIC_SDA=0;
	CT_Delay();
	XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
	CT_Delay();
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
}
//������ACKӦ��
void CT_IIC_NAck(void)
{
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	XGpio_DiscreteWrite(&touch_sda, 1, 1);					//CT_IIC_SDA=1;
	CT_Delay();
	XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
	CT_Delay();
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void CT_IIC_Send_Byte(u8 txd)
{
    u8 t;
	CT_SDA_OUT();
	XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	CT_Delay();
	for(t=0;t<8;t++)
    {
		XGpio_DiscreteWrite(&touch_sda, 1, (txd & 0x80) >> 7);				//CT_IIC_SDA=(txd&0x80)>>7;
        txd <<= 1;
        XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
		CT_Delay();
		XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
		CT_Delay();
    }

}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
	Delay_us(10);
	for(i=0;i<8;i++ )
	{
		XGpio_DiscreteWrite(&touch_scl, 1, 0);					//CT_IIC_SCL=0;
		CT_Delay();
		XGpio_DiscreteWrite(&touch_scl, 1, 1);					//CT_IIC_SCL=1;
		receive <<= 1;
		if(XGpio_DiscreteRead(&touch_sda, 1))
			receive++;
	}
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK
 	return receive;
}




























