
#include "display/LCD.h"
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <xparameters.h>
#include <xintc.h>
#include <xtmrctr.h>
#include <xparameters.h>
#include "display/delay.h"
#include "touch/ctiic.h"
#include "touch/delay.h"
#include "touch/gt9147.h"
#include "touch/touch.h"
#include "touch/delay.h"

#include <string.h>
#include <stdlib.h>




#include"my_caculator/my_caculator.h"
#include "/mnt/sdb1/Project/FPGA2018/caulator_2018/caulator_2018.sdk/mbtest/src/caculate/caltor.h"
XTmrCtr timer;
XIntc intc;
volatile u8 a=0;
volatile u8 KeyAction=0;
volatile u8 KeyLast=0;
u8 KeyCnt=10;


extern char input;
extern u8 point=0;
volatile u16 Keyx;
volatile u16 Keyy;

extern int add=1;
XIntc intc;


extern volatile  int k=0;


static int ca=0;

Node MyExperession[NODE_MAX]={0};
float myfloatt=0.0001;
char result[20];

extern   char MyExperission[50];

double mode=0;
long int value;
double f_deal=10;
int a_deal=5;
extern int keyvalue[20];
extern long int temp ;
////////////////////////////////////////////////////////////////////////////////
void Timer_ISR(void *arg,u8 num)
{
	if(KeyCnt<15)KeyCnt++;
	KeyLast = KeyAction;
	KeyAction=GT9147_Scan(0);
	a=(KeyAction&&KeyLast==0&&KeyCnt==15)?1:0;
	if(a)
	{
	 a = 0;
	 KeyCnt = 0;
	 ca=keypress(&mode,&value,&f_deal,&a_deal);
	}
	 Keyx=tp_dev.x[0];
	 Keyy=tp_dev.y[0];
}
int main(void)
	{


		u16 x,y;
		u32 x0;
		int i;
        int state=1;
		init_platform();


		LCD_Init();
		LCD_Clear(BLACK);
//        while(1)
//        {
//		for(i=10;i!=0;i--)
//		{
//			LCD_Init();
//			LCD_Clear(BLACK);
//			LCD_Clear(RED);
//		}
//		i=0;
//        }
		TP_Init();

		XIntc_Initialize(&intc, XPAR_INTC_0_DEVICE_ID);
		XIntc_Start(&intc, XIN_REAL_MODE);
		Xil_ExceptionInit();
		Xil_ExceptionRegisterHandler(
				XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XIntc_InterruptHandler,
				&intc
		);
		Xil_ExceptionEnable();

		XTmrCtr_Initialize(&timer, XPAR_HIER_PERIPH_AXI_TIMER_0_DEVICE_ID);
		XTmrCtr_SetResetValue(&timer, 0, XPAR_HIER_PERIPH_AXI_TIMER_0_CLOCK_FREQ_HZ/500 - 1);
		XTmrCtr_SetOptions(&timer,0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION | XTC_DOWN_COUNT_OPTION);
		XTmrCtr_SetHandler(&timer, Timer_ISR,(void *)&timer);
		XIntc_Connect(&intc, XPAR_INTC_0_TMRCTR_0_VEC_ID, XTmrCtr_InterruptHandler, (void*)&timer);
		XIntc_Enable(&intc, XPAR_INTC_0_TMRCTR_0_VEC_ID);
		XIntc_Acknowledge(&intc,XPAR_INTC_0_TMRCTR_0_VEC_ID);
		XIntc_Start(&intc, 0);
		XTmrCtr_Start(&timer, 0);

		showmenu();
	  LCD_ShowString(365,80,200,24,24,"BASE   ");
        while(1)
        {
        	int count;
//        	a=GT9147_Scan(0);
//        	KeyAction=1;
//           if(a)
//           {
//        	   for(i=0;i<4;i++)
//			  {
//        		  delay_ms(5);
//        		  if( Keyx==tp_dev.x[0]&&
//             	 Keyy==tp_dev.y[0])
//        			  KeyAction=0;
//			  }
//
//           }
//       	if(a)
//        	{
//       		 a = 0;
//       		 KeyCnt = 0;
//        		 ca=keypress(&mode,&value,&f_deal,&a_deal);
//            }
        	delay_ms(1000);
        	 if(ca)
			 {
				 ca=0;
				 if(mode==0)
				 {
				 }
				 else if(mode==1||mode==3)
				 {
				 }
				 else if(mode==2)
				 {
				 }

			 }


         }



}


