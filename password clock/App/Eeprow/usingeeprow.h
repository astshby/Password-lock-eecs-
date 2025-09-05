#ifndef usingeeprow_H
#define usingeeprow_H

#include "public.h"
#include <intrins.h> // 用于_nop_()

// 假设你的三个字符数组的长度
#define SECRET1_LEN 7
#define SECRET2_LEN 7
#define SECRET3_LEN 7

// 定义三个数组在EEPROM中的起始地址。
// **非常重要**：这些地址必须在芯片的EEPROM地址范围内，并且不能重叠！
#define SECRET1_EEPROM_ADDR 0x2200  // 扇区1: 0x2000-0x21FF
#define SECRET2_EEPROM_ADDR 0x2400  // 扇区2: 0x2200-0x23FF  
#define SECRET3_EEPROM_ADDR 0x2600  // 扇区3: 0x2400-0x25FF
#define INIT_FLAG_ADDR 0x2000  //保存判断位

// 定义IAP/ISP相关的特殊功能寄存器(SFR)
sfr IAP_DATA   = 0xE2; // IAP数据寄存器
sfr IAP_ADDRH  = 0xE3; // IAP地址高字节
sfr IAP_ADDRL  = 0xE4; // IAP地址低字节
sfr IAP_CMD    = 0xE5; // IAP命令寄存器
sfr IAP_TRIG   = 0xE6; // IAP触发寄存器
sfr IAP_CONTR  = 0xE7; // IAP控制寄存器

// IAP命令定义
#define IAP_IDLE    0x00  // 空闲模式
#define IAP_READ    0x01  // 读命令
#define IAP_WRITE   0x02  // 写命令
#define IAP_ERASE   0x03  // 擦除命令

// 设置IAP_CONTR寄存器的值：使能IAP，并设置等待时间（系统时钟频率不同，值不同）
// 假设使用11.0592MHz时钟，设置等待时间为：0x02 (2个时钟周期) 或根据手册推荐值
#define ENABLE_IAP  0x81 // 使能IAP (bit7: IAPEN=1), 并设置等待时间

void Arrays_LoadFromEEPROM();
void Arrays_SaveToEEPROM(uchar secret_code);
void Initialize_EEPROM();
void IapIdle();
uchar IapReadByte(uint addr);
void IapWriteByte(uint addr, uchar dat);
void IapEraseSector(uint addr);

#endif