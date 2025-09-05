#ifndef usingeeprow_H
#define usingeeprow_H

#include "public.h"
#include <intrins.h> // ����_nop_()

// ������������ַ�����ĳ���
#define SECRET1_LEN 7
#define SECRET2_LEN 7
#define SECRET3_LEN 7

// ��������������EEPROM�е���ʼ��ַ��
// **�ǳ���Ҫ**����Щ��ַ������оƬ��EEPROM��ַ��Χ�ڣ����Ҳ����ص���
#define SECRET1_EEPROM_ADDR 0x2200  // ����1: 0x2000-0x21FF
#define SECRET2_EEPROM_ADDR 0x2400  // ����2: 0x2200-0x23FF  
#define SECRET3_EEPROM_ADDR 0x2600  // ����3: 0x2400-0x25FF
#define INIT_FLAG_ADDR 0x2000  //�����ж�λ

// ����IAP/ISP��ص����⹦�ܼĴ���(SFR)
sfr IAP_DATA   = 0xE2; // IAP���ݼĴ���
sfr IAP_ADDRH  = 0xE3; // IAP��ַ���ֽ�
sfr IAP_ADDRL  = 0xE4; // IAP��ַ���ֽ�
sfr IAP_CMD    = 0xE5; // IAP����Ĵ���
sfr IAP_TRIG   = 0xE6; // IAP�����Ĵ���
sfr IAP_CONTR  = 0xE7; // IAP���ƼĴ���

// IAP�����
#define IAP_IDLE    0x00  // ����ģʽ
#define IAP_READ    0x01  // ������
#define IAP_WRITE   0x02  // д����
#define IAP_ERASE   0x03  // ��������

// ����IAP_CONTR�Ĵ�����ֵ��ʹ��IAP�������õȴ�ʱ�䣨ϵͳʱ��Ƶ�ʲ�ͬ��ֵ��ͬ��
// ����ʹ��11.0592MHzʱ�ӣ����õȴ�ʱ��Ϊ��0x02 (2��ʱ������) ������ֲ��Ƽ�ֵ
#define ENABLE_IAP  0x81 // ʹ��IAP (bit7: IAPEN=1), �����õȴ�ʱ��

void Arrays_LoadFromEEPROM();
void Arrays_SaveToEEPROM(uchar secret_code);
void Initialize_EEPROM();
void IapIdle();
uchar IapReadByte(uint addr);
void IapWriteByte(uint addr, uchar dat);
void IapEraseSector(uint addr);

#endif