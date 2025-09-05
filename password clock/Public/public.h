#ifndef _public_H
#define _public_H      //多文件一定有ifndef，define，endif 

#include<reg52.h>
#include "globals.h"

typedef unsigned int uint;	
typedef unsigned char uchar;
typedef unsigned long ulong;

//延时函数，延时10us与1ms
void delay_us(uint ten_us);
void delay_ms(uint ms);

#endif
