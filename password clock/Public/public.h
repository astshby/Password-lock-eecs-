#ifndef _public_H
#define _public_H      //���ļ�һ����ifndef��define��endif 

#include<reg52.h>
#include "globals.h"

typedef unsigned int uint;	
typedef unsigned char uchar;
typedef unsigned long ulong;

//��ʱ��������ʱ10us��1ms
void delay_us(uint ten_us);
void delay_ms(uint ms);

#endif
