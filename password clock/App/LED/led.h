#ifndef _led_H
#define _led_H

#include "public.h"

#define led_data P0
sbit pin2 = P2^2;  
sbit pin3 = P2^3;  
sbit pin4 = P2^4; 

void led_show(uchar *str);
void led_paused();
void num();
void del();
void change_num();
void change_del();

#endif