/*
 * my_caculator.c
 *
 *  Created on: 2017��11��11��
 *      Author: 87123
 */
#include "/mnt/sdb1/Project/FPGA2018/caulator_2018/caulator_2018.sdk/mbtest/src/display/LCD.h"
#include"/mnt/sdb1/Project/FPGA2018/caulator_2018/caulator_2018.sdk/mbtest/src/touch/touch.h"

double myfloat;

 int input;
 u8 point;

 int keyvalue[20];
  char MyExperission[50];
  long int temp ;//used to store the keypress value

 int add;

extern int ab;
volatile  int k;
char pin[20];
void showmenu(void)
{
	POINT_COLOR=WHITE;

	//		LCD_ShowNum(40+24,160,x0,4,24);

	        LCD_DrawRectangle(20,20,470,170);

			LCD_ShowString(65,220,200,24,24,"1");
			LCD_DrawRectangle(40,200,105,270);
			LCD_ShowString(145,220,200,24,24,"2");
			LCD_DrawRectangle(120,200,185,270);
			LCD_ShowString(225,220,200,24,24,"3");
			LCD_DrawRectangle(200,200,265,270);
			LCD_ShowString(305,220,200,24,24,"+");
			LCD_DrawRectangle(280,200,345,270);
			LCD_ShowString(375,230,200,24,24,"BASE");
			LCD_DrawRectangle(360,200,475,270);


			LCD_ShowString(65,320,200,24,24,"4");
			LCD_DrawRectangle(40,300,105,370);
			LCD_ShowString(145,320,200,24,24,"5");
			LCD_DrawRectangle(120,300,185,370);
			LCD_ShowString(225,320,200,24,24,"6");
			LCD_DrawRectangle(200,300,265,370);
			LCD_ShowString(305,320,200,24,24,"-");
			LCD_DrawRectangle(280,300,345,370);
			LCD_ShowString(375,320,200,24,24,"AM/FM");
			LCD_DrawRectangle(360,300,475,370);


			LCD_ShowString(65,420,200,24,24,"7");
			LCD_DrawRectangle(40,400,105,470);
			LCD_ShowString(145,420,200,24,24,"8");
			LCD_DrawRectangle(120,400,185,470);
			LCD_ShowString(225,420,200,24,24,"9");
			LCD_DrawRectangle(200,400,265,470);
			LCD_ShowString(305,420,200,24,24,"FM");
			LCD_DrawRectangle(280,400,345,470);
			LCD_ShowString(375,420,200,24,24,"ASK/PSK");
			LCD_DrawRectangle(360,400,475,470);


			LCD_ShowString(65,520,200,24,24,"0");
			LCD_DrawRectangle(40,500,105,570);
			LCD_ShowString(140,520,200,24,24,"AM+");
			LCD_DrawRectangle(120,500,185,570);
			LCD_ShowString(215,520,200,24,24,"AM-");
			LCD_DrawRectangle(200,500,265,570);
			LCD_ShowString(305,520,200,24,24,"/");
			LCD_DrawRectangle(280,500,345,570);
			LCD_ShowString(375,520,200,24,24,"sin");
			LCD_DrawRectangle(360,500,425,570);


			LCD_ShowString(65,620,200,24,24,"ln");
			LCD_DrawRectangle(40,600,105,670);
			LCD_ShowString(140,620,200,24,24,"lg");
			LCD_DrawRectangle(120,600,185,670);
			LCD_ShowString(210,620,200,24,24,"asin");
			LCD_DrawRectangle(200,600,265,670);
			LCD_ShowString(295,620,200,24,24,"tan");
			LCD_DrawRectangle(280,600,345,670);
			LCD_ShowString(375,620,200,24,24,"cos");
			LCD_DrawRectangle(360,600,425,670);


			LCD_ShowString(65,720,200,24,24,"AC");
			LCD_DrawRectangle(40,700,105,770);
			LCD_ShowString(135,720,200,24,24,"DEL");
			LCD_DrawRectangle(120,700,185,770);
			LCD_ShowString(225,720,200,24,24,"DO");
			LCD_DrawRectangle(200,700,265,770);
			LCD_ShowString(290,720,200,24,24,"atan");
			LCD_DrawRectangle(280,700,345,770);
			LCD_ShowString(370,720,200,24,24,"acos");
			LCD_DrawRectangle(360,700,425,770);

			LCD_ShowString(20,420,200,24,24,".");
			LCD_DrawRectangle(0,400,35,470);
}

int keypress(double* mode,long int *value,double *f_deal,int *a_deal)
{
	u8 t=0;
	u8 i=0;
    u8 caflag=0;
	u16 lastpos[5][2];
	POINT_COLOR=WHITE;
	LCD_ShowString(225,720,200,24,24,"DO");
	if(temp==0)
	LCD_Fill(60,80,300,110,BLACK);
		double keyinput = 0;//final return value
		int sure;//decide the final return value

//printf("key\n");
		if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<270&&tp_dev.y[0]>200)
		{
			    temp*=10;
				 temp+=1;
				 sprintf(pin,"%d",temp);
				 LCD_ShowString(60,80,200,24,24,pin);
//				 point +=10;
//				 LCD_ShowString(60+point,80,200,24,24,"1");
				 if(point==500)point = 0;
				 caflag=0;

		}

		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<270&&tp_dev.y[0]>200)
		{
			  temp*=10;
			 temp+=2;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
//				 point +=10;
//				 LCD_ShowString(60+point,80,200,24,24,"2");
				 if(point==500)point = 0;
				 caflag=0;

		}

		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<270&&tp_dev.y[0]>200)
		{
			 temp*=10;
						 temp+=3;
						 sprintf(pin,"%d",temp);
						 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"3");
				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<270&&tp_dev.y[0]>200)
		{
//				 input=;

			 temp+=100;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"+");
				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<475&&tp_dev.y[0]<270&&tp_dev.y[0]>200)
		{
			     *mode = 0;
			     temp = 0;
			     LCD_Fill(25,25,465,165,WHITE);
			     LCD_ShowString(365,80,200,24,24,"BASE   ");
//				 LCD_ShowString(60+point,80,200,24,24,"^");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='+';
//                                 k++;
		}



		else if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<370&&tp_dev.y[0]>300)
		{
			 temp*=10;
						 temp+=4;
						 sprintf(pin,"%d",temp);
						 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"4");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='4';
//                                 k++;
		}
		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<370&&tp_dev.y[0]>300)
		{
			temp*=10;
			 temp+=5;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"5");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='5';
//                                 k++;
		}
		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<370&&tp_dev.y[0]>300)
		{
			temp*=10;
					 temp+=6;
					 sprintf(pin,"%d",temp);
					 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"6");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='6';
//                                 k++;
		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<370&&tp_dev.y[0]>300)
		{
			 temp-=100;
					 sprintf(pin,"%d",temp);
					 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"-");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='-';
//                                 k++;
		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<475&&tp_dev.y[0]<370&&tp_dev.y[0]>300)
		{
			temp = 0;
				 if(*mode == 1)
					 {*mode = 3;
				 LCD_Fill(25,25,465,165,WHITE);
				 LCD_ShowString(365,80,200,24,24,"AM/FM  ");
				 LCD_ShowString(60,110,200,24,24,"FM");
					 }
				 else
				 {
					 *mode = 1;
					 LCD_Fill(25,25,465,165,WHITE);
					 LCD_ShowString(365,80,200,24,24,"AM/FM  ");
					 LCD_ShowString(60,110,200,24,24,"AM");
				 }
//				 LCD_ShowString(60+point,80,200,24,24,"(");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='-';
//                                 k++;
		}




		else if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
		{
			temp*=10;
					 temp+=7;
					 sprintf(pin,"%d",temp);
					 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"7");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='7';
//                                 k++;
		}
		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
		{
			temp*=10;
			 temp+=8;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"8");
				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
		{
			temp*=10;
			 temp+=9;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
			 //				 LCD_ShowString(60+point,80,200,24,24,"9");
				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
		{
				if(*mode==3)
				{
					if(*f_deal==5)
						{*f_deal=10;
					 LCD_ShowString(365,110,200,24,24,"FM=10");
						}
					else
					{
						*f_deal=5;
					LCD_ShowString(365,110,200,24,24,"FM=5 ");
					}
				}
//				 LCD_ShowString(60+point,80,200,24,24,"*");
				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<475&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
		{
				*mode = 2;
				temp = 0;
				 LCD_Fill(25,25,465,165,WHITE);
				 LCD_ShowString(365,80,200,24,24,"ASK/PSK");
//				 LCD_ShowString(60+point,80,200,24,24,")");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='*';
//                                 k++;
		}




		else if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<570&&tp_dev.y[0]>500)
		{
			temp*=10;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
//				 LCD_ShowString(60+point,80,200,24,24,"0");
				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='0';
//                                 k++;
		}
		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<570&&tp_dev.y[0]>500)
		{
//				 pi
          if(*mode==1){
			if(*a_deal==10) *a_deal =1;
			else *a_deal+=1;
			sprintf(pin,"AM=%d ",*a_deal);
		   LCD_ShowString(365,50,200,24,24,pin);

          }
          add=0;
          caflag=0;
		}
		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<570&&tp_dev.y[0]>500)
		{
//				 exp
			if(*mode==1){
			if(*a_deal==1) *a_deal =10;
		   else *a_deal-=1;
			sprintf(pin,"AM=%d ",*a_deal);
		   LCD_ShowString(365,50,200,24,24,pin);
			}
			 caflag=0;



		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<570&&tp_dev.y[0]>500)
		{
				 input='/';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"/");
				 if(point==500)point = 0;
				 caflag=0;
		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<425&&tp_dev.y[0]<570&&tp_dev.y[0]>500)
		{
				 input='s';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"s");
				 MyExperission[k++]=input;

				 input='i';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"i");
				 MyExperission[k++]=input;

				 input='n';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"n");

				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='/';
//                                 k++;
		}



		else if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<670&&tp_dev.y[0]>600)
		{
				 input='l';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"l");
				 MyExperission[k++]=input;

				 input='n';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"n");



				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='0';
//                                 k++;
		}
		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<670&&tp_dev.y[0]>600)
		{
				 input='l';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"l");
				 MyExperission[k++]=input;


				 input='g';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"g");
				 if(point==500)point = 0;
				 caflag=0;
//								 k--;
//								 add=0;
		}
		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<670&&tp_dev.y[0]>600)
		{
				 input='a';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"a");
				 MyExperission[k++]=input;

				 input='s';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"s");
				 MyExperission[k++]=input;

				 input='i';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"i");
				 MyExperission[k++]=input;

				 input='n';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"n");
				 caflag=0;

		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<670&&tp_dev.y[0]>600)
		{
				 input='t';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"t");

				 input='a';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"a");
				 MyExperission[k++]=input;

				 input='n';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"n");

				 if(point==500)point = 0;
				 caflag=0;
//								  MyExperission[k]='/';
//                                 k++;
		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<425&&tp_dev.y[0]<670&&tp_dev.y[0]>600)
		{
				 input='c';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"c");
				 MyExperission[k++]=input;

				 input='o';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"o");
				 MyExperission[k++]=input;

				 input='s';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"s");

				 if(point==500)point = 0;
				 caflag=0;
		}




		else if(tp_dev.x[0]>40&&tp_dev.x[0]<105&&tp_dev.y[0]<770&&tp_dev.y[0]>700)
		{
			 k=0;
			 point =0;
			 LCD_Fill(60,80,300,110,BLACK);
			 temp = 0;
			 sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
			 add=0;
			 caflag=0;
		}
		else if(tp_dev.x[0]>120&&tp_dev.x[0]<185&&tp_dev.y[0]<770&&tp_dev.y[0]>700)
		{
             if(temp==0) temp = 0;
             else temp=(int)(temp/10);
			 LCD_Fill(60,80,300,110,BLACK);
			sprintf(pin,"%d",temp);
			 LCD_ShowString(60,80,200,24,24,pin);
			 add=0;
			 caflag=0;
		}
		else if(tp_dev.x[0]>200&&tp_dev.x[0]<265&&tp_dev.y[0]<770&&tp_dev.y[0]>700)
		{
         int i=0,j=0;
            *value = temp;
			point = 0;
			caflag=1;
           sprintf(pin,"%d",(*value));
		   LCD_ShowString(60,80,200,24,24,pin);
		   POINT_COLOR=BLUE;
		   	LCD_ShowString(225,720,200,24,24,"DO");
		}
		else if(tp_dev.x[0]>280&&tp_dev.x[0]<345&&tp_dev.y[0]<770&&tp_dev.y[0]>700)
		{
				 input='a';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"a");

				 input='t';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"t");
				 MyExperission[k++]=input;

				 input='a';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"a");
				 MyExperission[k++]=input;

				 input='n';
				 point+=10;
				 LCD_ShowString(60+point,80,200,24,24,"n");

				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>360&&tp_dev.x[0]<425&&tp_dev.y[0]<770&&tp_dev.y[0]>700)
		{
				 input='a';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"a");
				 MyExperission[k++]=input;

				 input='c';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"c");
				 MyExperission[k++]=input;

				 input='o';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"o");
				 MyExperission[k++]=input;

				 input='s';
				 point +=10;
				 LCD_ShowString(60+point,80,200,24,24,"s");


				 if(point==500)point = 0;
				 caflag=0;

		}
		else if(tp_dev.x[0]>0&&tp_dev.x[0]<45&&tp_dev.y[0]<470&&tp_dev.y[0]>400)
				{
					 input='.';
					 point +=10;
					 LCD_ShowString(60+point,80,200,24,24,".");
				}





		if(add)
		{
			keyvalue[k++] = input;

		}
		else add=1;




        return caflag;

	}
