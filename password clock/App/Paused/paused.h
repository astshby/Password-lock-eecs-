#ifndef _paused_H
#define _paused_H

#include "public.h"
#include "led.h"
#include "beep.h"
#include "lcd1602.h"

sbit LED_paused=P2^1; 

void paused_start();
void paused_stop();
void paused_min();   //ͷ�ļ�����Ҫ�жϱ��
#endif