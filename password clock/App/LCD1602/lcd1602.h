#ifndef _lcd1602_H
#define _lcd1602_H

#include "public.h"

//�ܽŶ���
sbit  LCD1602_RS=P2^6;//��������ѡ��
sbit  LCD1602_RW=P2^5;//��дѡ��
sbit  LCD1602_E=P2^7;//ʹ���ź�
#define LCD1602_data P0	//�궨��LCD1602���ݶ˿�

//��������
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
