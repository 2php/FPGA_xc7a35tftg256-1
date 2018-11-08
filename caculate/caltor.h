/*
 * caltor.h
 *
 *  Created on: 2017ƒÍ11‘¬11»’
 *      Author: 87123
 */

#ifndef SRC_CACULATE_CALTOR_H_
#define SRC_CACULATE_CALTOR_H_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_MAX 1000
#define NODE_MAX 500
#define NUM_OPT 20
#define LEN_OPT 6
#define NUM_OPS 200
#define exp  2.718
#define pi 3.1416
typedef enum{
    Opd=0,
    Opt=1
}Type;
typedef struct{
    int opt;
    double opd;
    Type tp;
}Node;

//¿®∫≈’ª£¨ºÏ≤‚¿®∫≈ «∑Ò∆•≈‰
char brackets[NUM_OPS];
int bb=0;
int input1(Node *in,char*IMyExperession);
int translate(char *p,Node *re,int *len);
double translateopd(char *p,int *len);
int translateopt(char *p,int *len);
int cmp(const char *s,const char *d);

int sclt(int opr,double *opd);
int dclt(int opr,double *opd1,double opd2);
int prid(int c);
int calculate(Node *n,double*r)  ;
int FlToCh(float  myfloat,char * oToLcd);
#endif /* SRC_CACULATE_CALTOR_H_ */
