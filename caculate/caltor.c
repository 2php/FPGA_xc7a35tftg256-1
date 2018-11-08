#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
  
#define INPUT_MAX 1000  
#define NODE_MAX 500  
#define NUM_OPT 20  
#define LEN_OPT 6  
#define NUM_OPS 200  
#define z  3.141593
#define e  2.718282

typedef enum{  
    Opd=0,  
    Opt=1  
}Type;  
typedef struct{  
    int opt;  
    double opd;  
    Type tp;  
}Node;  
  
//����ջ����������Ƿ�ƥ��  
char brackets[NUM_OPS];  

int input1(Node *in,char*IMyExperession);
int translate(char *p,Node *re,int *len);  
double translateopd(char *p,int *len);  
int translateopt(char *p,int *len);  
int cmp(const char *s,const char *d);  
int calculate(Node *n,double *r);  
int sclt(int opr,double *opd);  
int dclt(int opr,double *opd1,double opd2);  
int prid(int c);  
int calculate(Node *n,double*r)  ;
int ab=0;
/*���ܣ����ʽ�����ת�� 
 *      �������벢����Ϊ�������Ͳ�����������ʽ�� 
 *���룺���ʽ���ĵ�ַ 
 *�����ִ��״̬����ȷ����1,���󷵻�0 
 */  
int input1(Node *in,char*ins)
{  
    //input->string  
 //   char ins[INPUT_MAX]={0};  
    int insi=0;  
    char temp_in=0;  
    int len=0;  
   //��⿪ͷ�Ŀո�
    while(' '==(ins[0]))insi++; 
 //   while(' '==(ins[0]=getchar()));  
    //����ǲ���ֱ��������һ���س�  
  /*  if(ins[0]!='\0')
    {  
        do{  
            temp_in=ins[insi]; 
			insi++; 
            //ֻ�ܺ��Զ���ո�  
            if(ins[insi]==' '&&temp_in==' ')  
                continue;  
            ins[++insi]=temp_in;  
        }while(temp_in!='\0');  
        ins[insi]=0;  
    } 
    insi=0;  
    //����س�ֱ�����0  
*/
//    if(ins[0]=='\0')
//        in->tp=Opd,in->opd=0.0,in++;
//    else
        //ѹ����ʽ��  
        while(ins[insi])  
        {  
            if(translate(ins+insi,in++,&len))  
                insi+=len;  
            else  
                return 0;  
        }  
    //�Զ���ӵȺ�  
    if((in-1)->opt!='=')  
        in->opt='=',in->tp=Opt,in++;  
    in->opt=-1,in->tp=Opt;  
    return 1;  
}  
/*���ܣ������ַ���Ϊ������������� 
 *���룺�ַ�����ַ�����뷵�ؽڵ㣬�������Ͳ��������ȷ��ص�ַ 
 *�����������״̬ 
 */  
int translate(char *p,Node *re,int *len)  
{  
    if(*p>='0'&&*p<='9')  
    {  
        re->tp=Opd;  
        re->opd=translateopd(p,len);  
        return 1;  
    }  
    else if(*p=='e'||*p=='p')  
    {  
        if(*p=='e')  
        {  
            re->tp=Opd;  
            re->opd=M_E;  
            *len=1;  
            if(p[1]==' ')  
                (*len)++;   //ʮ����Ҫ���˴����������  
            return 1;  
        }  
        else  
        {  
            if(p[1]=='i')  
            {  
                re->tp=Opd;  
                re->opd=M_PI;  
                *len=2;  
                if(p[2]==' ')  
                    (*len)++;  
                return 1;  
            }  
            else  
                return 0;  
        }  
    }  
    else  
    {  
        re->tp=Opt;  
        re->opt=translateopt(p,len);  
        if(re->opt)  
            return 1;  
        else  
            return 0;  
    }  
}  
/*���ܣ���������� 
 */  
double translateopd(char *p,int *len)  
{  
    int flag=0;  
    int pointnum=1;  
    double temp=0;  
    int i=0;  
    do{  
        if(!flag&&p[i]!='.')  
            temp=temp*10+p[i++]-'0';  
        else if(!flag&&p[i]=='.')  
            flag=1,i++;  
        else  
            temp+=(p[i++]-'0')*pow(0.1,pointnum),pointnum++;  
    }while((p[i]>='0'&&p[i]<='9')||p[i]=='.');  
    if(p[i]==' ')  
        i++;
    *len=i;  
    return temp;  
}  
/*���ܣ���������� 
 *      ���������Ƿ����򷵻�0���Ϸ��򷵻ط����־ 
 */  
int translateopt(char *p,int *len)  
{  
    char fu[NUM_OPT][LEN_OPT]={"+","-","*","/","^","(",")","sin","cos","tan","asin","acos","atan","ln","lg","="};  
    int fu_int[NUM_OPT]={'+','-','*','/','^','(',')','s','c','t','s'+'a','c'+'a','t'+'a','n','g','='};  
    int i=0;  
    for(i=0;i<NUM_OPT;i++)  
    {  
        if(*len=cmp(p,fu[i]))  
            break;  
    }  
    if(i==NUM_OPT)  
        return 0;
    if(p[*len]==' ')
        (*len)++;  
    return fu_int[i];  
}  
/*���ܣ��ַ����Ƚϣ������ַ����� 
 *      ��ƥ�䷵��0 
 */  
int cmp(const char *s,const char *d)  
{  
    char *dd=(char*)d;  
    while(*d)  
        if(*(d++)!=*(s++))  
            return 0;  
    return d-dd;  
}  
/*���ܣ����㺯�� 
 *���룺���ʽ����ַ�����������ص�ַ 
 *������ɹ���� 
 */  
int calculate(Node *n,double *r)
{  
    //˫��ջ  
    double OPRD[NUM_OPS]={0};  
    int OPRT[NUM_OPS]={0};  
    int db=0;  
    int tb=0;  
  
    int top=0;  
    double a=0.0,b=0.0;  
    int o=0;  
    int len=0;  
    Node *nb=n;  
  
    if(n->tp==Opt&&n->opt=='-')  
        OPRD[db]=0.0,db++;  //Push(&OPRD,0.0);   
    while(1)  
    {  
        //�ж�ǰ����û�и���  
        if(n->tp==Opd)
        {
            OPRD[db]=n->opd,db++,n++;    //Push(&OPRD,n->opd),n++;
        }
        else
        {  
            //˫Ŀ�����  
            if(prid(n->opt))  
            {  
                //if(!GetTop(OPRT,&top))  
                if(tb)  
                    top=OPRT[tb-1];  
                if(!tb)  
                {  
                    if(n->opt=='='||n->opt==')')  
                    {  
                        if(n->opt==')')  
                        {  
                            ab--;   //if(!Pop(&brackets,&temp))
                            if(ab<0)
                            {  
                                printf("Bracket does not match!");  
                                return 0;  
                            }  
                        }  
                        break;  
                    }  
                    else  
                        OPRT[tb]=n->opt,tb++,n++;    //Push(&OPRT,n->opt),n++;  
                    continue;  
                }  
                if(prid(top)==0)  
                {  
                    //Pop(&OPRD,&a);  
                    //Pop(&OPRT,&o);  
                    db--;  
                    a=OPRD[db];  
                    tb--;  
                    o=OPRT[tb];  
                    if(sclt(o,&a))  
                    {  
                        OPRD[db]=a,db++;    //Push(&OPRD,a);  
                        continue;  
                    }  
                    else  
                        return 0;  
                }  
                if(prid(top)>=prid(n->opt))  
                {  
                    //Pop(&OPRD,&b);  
                    //Pop(&OPRD,&a);  
                    //Pop(&OPRT,&o);  
                    db--;  
                    b=OPRD[db];  
                    db--;  
                    a=OPRD[db];  
                    tb--;  
                    o=OPRT[tb];  
                    if(dclt(o,&a,b))  
                    {  
                        OPRD[db]=a,db++;    //Push(&OPRD,a);  
                    }  
                    else  
                        return 0;  
                }  
                else  
                {  
                    OPRT[tb]=n->opt,tb++,n++;    //Push(&OPRT,n->opt),n++;  
                }  
            }  
            else
            {
                //��Ŀ�����������
                double x=0.0;
                if(n->opt=='(')
                {
                    brackets[ab]='(';
                    ab++;  //Push(&brackets,'(');
                    if(len=calculate((n+1),&x))
                    {
                        OPRD[db]=x;
                        db++;    //Push(&OPRD,x);
                        n+=len,n++;
                        if(n->tp==Opt&&n->opt==-1)
                        {
                            printf("Bracket does not match!");
                            return 0;
                        }
                    }
                    else
                        return 0;
                }
                else  
                {  
                    OPRT[tb]=n->opt,tb++;    //Push(&OPRT,n->opt);  
                    n++;  
                }  
            }  
        }  
    }  

   *r=OPRD[db-1];
//    printf("r=%lf\n");
   return n-nb+1;
}
/*���ܣ���Ŀ���� 
 */  
int sclt(int opr,double *opd)  
{  
    switch(opr)  
    {  
    case 's':  
        *opd=sin(*opd);  
        break;  
    case 'c':  
        *opd=cos(*opd);  
        break;  
    case 't':  
        *opd=tan(*opd);  
        break;  
    case 'a'+'s':  
        if(*opd<-1||*opd>1)  
        {  
            printf("Beyond asin()!");  
            return 0;  
        }  
        else  
            *opd=asin(*opd);  
        break;  
    case 'a'+'c':  
        if(*opd<-1||*opd>1)  
        {  
            printf("Beyond acos()!");  
            return 0;  
        }  
        else  
            *opd=acos(*opd);  
        break;  
    case 'a'+'t':  
        if(*opd>-3.141592654/2&&*opd<3.141592654/2)  
            *opd=atan(*opd);  
        else  
        {  
            printf("Beyond atan()!");  
            return 0;  
        }  
        break;  
    case 'n':  
        if(*opd>0)  
            *opd=log(*opd);  
        else  
        {  
            printf("Beyond ln()!");  
            return 0;  
        }  
        break;  
    case 'g':  
        if(*opd>0)  
            *opd=log10(*opd);  
        else  
        {  
            printf("Beyond lg()!");  
            return 0;  
        }  
        break;  
    }  
    return 1;  
}  
/*���ܣ�˫Ŀ���� 
 */  
int dclt(int opr,double *opd1,double opd2)  
{  
    switch(opr)  
    {  
        case '+':  
            *opd1 = *opd1+opd2;break;  
        case '-':  
            *opd1 = *opd1-opd2;break;  
        case '*':  
            *opd1 = (*opd1)*opd2;break;  
        case '/':  
            if(opd2>pow(0.1,8)||opd2<0-pow(0.1,8))  
                *opd1 = (*opd1)/opd2;  
            else  
            {  
                printf("Error 1/0 !");  
                return 0;  
            }  
            break;  
        case '^':  
            *opd1 = pow(*opd1,opd2);break;  
    }  
    return 1;  
}  
/*���ܣ��ж����ȼ� 
 */  
int prid(int c)  
{  
    switch(c)  
    {  
        case '+':  
        case '-':  
        case '=':  
        case ')':  
        return 1;break;  
        case '*':  
        case '/':  
        return 2;break;  
        case '^':  
        return 3;break;  
        default :return 0;break;  
    }  
}  



int FlToCh(float  myfloat,char * oToLcd) //��float�ļ�����ת��char����ȥ��ʾ
{
//	float myfloat=4.1467;
	int a=(signed int) (myfloat);
	if(a<0) a=a*(-1);
	else a=a;
	int i,j,q,m;
	int k[12]={0};
	int temp1=0;
	int temp2=0;
	int judge =0;
	float myfloatt=0;
//	char oToLcd[10]={0};
	for(m=0;a>temp1;m++){
	if(temp1==0)
	temp1=temp1+10;
	else temp1=temp1*10;
	}

	q=m;
	int temp=10;
	temp1=a;
	for(i=0;i<q;i++)
	{
		if(q>1)
		{
		for(j=1;j<q;j++)
		temp=temp*10;
		temp=temp/10;        //     ���ֶ���ʮ�� ~�ó���
		while(temp>0)
		{
				k[i] = temp1/temp;
				temp1=temp1-k[i]*temp;//ÿ�δ洢ȥ�����λ֮��� A
				i++;
				temp=temp/10;
		}
		}
		else k[i]=temp1;
	}
///////////////////��������	       //////////////////С������  �ֽ�
	q=6;
	 temp=10;
	 if((int)(myfloat)>=0)
	 temp2=(int)(myfloat*1000000)-a*1000000;
	 else {
	 	myfloatt=-myfloat;
	 temp2=(int)(myfloatt*1000000)-a*1000000;
	 }
	 
	temp1=temp2;
	for(i=m;i<q+3;i++)
	{
		if(q>1)
		{
		for(j=1;j<q;j++)
		temp=temp*10;
		temp=temp/10;//����ʱ���ֶ���ʮ�� ~�ó���
		while(temp>0)
		{
				k[i] = temp1/temp;
				temp1=temp1-k[i]*temp;//ÿ�δ洢ȥ�����λ֮��� A
				i++;
				temp=temp/10;
		}
		}
		else k[i]=temp1;
}


			int fff=0;
			if(((int)myfloat<0)) {//���� 
			oToLcd[0]='-';
			
			fff+=1;
			
			}
			
			for(i=0;i<m+7;i++)    //����С���㹲 m+5λ
			{

				if((i!=m)||(judge==1)){
						oToLcd[fff]=(k[i]+'0');
						judge=0;
//						printf("%c",oToLcd[fff]);
//						printf("\n");
				}
				else{
					oToLcd[fff]='.';
					judge=1;          //�����ж�
					i--;
				}
				fff=fff+1;
			 }


//			 printf("\n");
//			 for(i=0;i<m+3;i++)        //С��������λ����ǰ��Ķ�λΪm+3λ
//			 printf("%d",k[i]);
//			 	 printf("\n");


//			 	for(i=0;i<m+4;i++)
//			printf("%c",oToLcd[i]);
		return 0 ;
}


/*int main()  //���������� 
{  
  //  int c=0;  
 //   while(1)  
   // {  
   int i=0;
        Node MyExperession[NODE_MAX]={0};  
        double myfloat=0.0;  
        char oToLcd[50]={0};
        char IMyExperession[50]={0};
        int j=0;
        gets (IMyExperession);
        //�������ջ  
 //      bb=0;   //InitStack(&brackets);  
        printf("Enter: ");  
        //����  
        
       if(!input(MyExperession,IMyExperession))  
        {  
            printf("Input Error!");  
   //         continue;  
        } 
        //����  
 //       if(calculate(nodes,&r))  
   //     {  
  /*          if(bb)  
            {  
                printf("Bracket does not match!");  
                continue;  
            }  
  
            calculate(MyExperession,&myfloat); //�Լ��ӵĶ���
//            printf("%lf",myfloat);//myfloat ������ȷ 
//              printf("\n");
            FlToCh(  myfloat, oToLcd);
		 
 //               printf("%.4f",myfloat);  
             
    //    }  
    for(;oToLcd[i]!='\0';i++){
	
    printf("%c",oToLcd[i]);
    printf("\n");
 // 
   }   
    return 0;  
}  */
