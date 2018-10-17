#ifndef _MAIN_H
#define _MAIN_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define NUM1 500
#define NUM2 500

typedef struct 
{
    char num[10];
    char name[20];
    char class[20];
    float sum;
}stu_infor;

typedef struct
{
    char class_num[10];
    char class_name[20];
    char class_pro[20];
    int teach_hour;
    float credit_hour;
    int class_peo_num;
    int class_peo_max;
}class_infor;

stu_infor stu[NUM1];
class_infor cla[NUM2];

#endif
