#ifndef _lcd1602_H
#define _lcd1602_H

#include "public.h"

//管脚定义
sbit  LCD1602_RS=P2^6;//数据命令选择
sbit  LCD1602_RW=P2^5;//读写选择
sbit  LCD1602_E=P2^7;//使能信号
#define LCD1602_data P0	//宏定义LCD1602数据端口

//函数声明
void lcd1602_clear();
void lcd1602_init();
void lcd1602_show(uchar x,uchar y,uchar *str);
void lcd1602_wake();
void lcd1602_stop();
void lcd1602_hello();
void lcd1602_welcome(uint i);
void lcd1602_away();
void lcd1602_bakabaka();
void lcd1602_restart();
void lcd1602_change_before(uchar secret_code);
void lcd1602_change_ok(uchar secret_code);
void lcd1602_change_stop(uchar secret_code);
void lcd1602_change_fin(uchar secret_code);
void lcd1602_change_away(uchar secret_code);
void lcd1602_change_restart(uchar secret_code);

#endif
