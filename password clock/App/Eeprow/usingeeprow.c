#include "usingeeprow.h"

//注意看文档对于各个口的定义
/* 关闭IAP功能 */
void IapIdle()
{
    IAP_CONTR = 0;    // 关闭IAP功能
    IAP_CMD = 0;      // 清除命令寄存器
    IAP_TRIG = 0;     // 清除触发寄存器
    IAP_ADDRH = 0xFF; // 将地址指向非EEPROM区域，防止误操作
    IAP_ADDRL = 0xFF;
}

/* 从EEPROM字节读取 */
uchar IapReadByte(uint addr)
{
    uchar dat; // 存储读出的数据

    IAP_CONTR = ENABLE_IAP;        // 使能IAP
    IAP_CMD = IAP_READ;            // 设置读命令
    IAP_ADDRL = addr;              // 设置目标地址低8位
    IAP_ADDRH = addr >> 8;          // 设置目标地址高8位

    // 触发命令 (先写0x5A, 再写0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // 等待操作完成
    _nop_();

    dat = IAP_DATA;                // 读取数据
    IapIdle();                     // 关闭IAP

    return dat;
}

/* 向EEPROM字节写入 */
void IapWriteByte(uint addr, uchar dat)
{
    IAP_CONTR = ENABLE_IAP;        // 使能IAP
    IAP_CMD = IAP_WRITE;           // 设置写命令
    IAP_ADDRL = addr;              // 设置目标地址低8位
    IAP_ADDRH = addr >> 8;          // 设置目标地址高8位
    IAP_DATA = dat;                // 准备要写入的数据

    // 触发命令 (先写0x5A, 再写0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // 等待操作完成
    _nop_();

    IapIdle();                     // 关闭IAP
}

/* 擦除EEPROM扇区 */
void IapEraseSector(uint addr)
{
    // 注意：擦除操作是针对整个扇区的！addr只需落在该扇区内即可。
    IAP_CONTR = ENABLE_IAP;        // 使能IAP
    IAP_CMD = IAP_ERASE;           // 设置擦除命令
    IAP_ADDRL = addr;              // 设置扇区地址低8位（地址只需在扇区内即可）
    IAP_ADDRH = addr >> 8;          // 设置扇区地址高8位

    // 触发命令 (先写0x5A, 再写0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // 等待操作完成（擦除时间较长）
    _nop_();

    IapIdle();                     // 关闭IAP
}

//功能函数
//  从EEPROM读取三个数组到RAM
void Arrays_LoadFromEEPROM()
{
    uint i;
    uint addr;

    // 读取数组1
    addr = SECRET1_EEPROM_ADDR;
    for (i = 0; i < SECRET1_LEN; i++) {
        secret_user1[i] = IapReadByte(addr++);
    }

    // 读取数组2
    addr = SECRET2_EEPROM_ADDR;
    for (i = 0; i < SECRET2_LEN; i++) {
        secret_user2[i] = IapReadByte(addr++);
    }

    // 读取数组3
    addr = SECRET3_EEPROM_ADDR;
    for (i = 0; i < SECRET3_LEN; i++) {
        secret_user3[i] = IapReadByte(addr++);
    }
}

// 2. 将三个数组从RAM写入EEPROM
void Arrays_SaveToEEPROM(uchar secret_code)
{
    uint i;
    uint addr;

    // **重要：STC的EEPROM写入前必须先擦除整个扇区！**
    // 假设数组1、2、3位于不同的扇区，或者你需要计算它们共同所在的扇区。
    // 这里为了简单，我们擦除每个数组所在的整个扇区。
    // 注意：擦除会清除整个扇区（通常是512字节），所以请确保你的数据布局不会因此丢失其他数据。
		
		switch(secret_code)
		{
			case 'a':
			{
				// 擦除数组1所在的扇区（使用数组1的起始地址）
				IapEraseSector(SECRET1_EEPROM_ADDR);
				// 写入数组1
				addr = SECRET1_EEPROM_ADDR;
				for (i = 0; i < SECRET1_LEN; i++) IapWriteByte(addr++, secret_user1[i]);
				break;
			}
			case 'b':
			{
				// 擦除数组2所在的扇区（使用数组1的起始地址）
				IapEraseSector(SECRET2_EEPROM_ADDR);
				// 写入数组2
				addr = SECRET2_EEPROM_ADDR;
				for (i = 0; i < SECRET2_LEN; i++) IapWriteByte(addr++, secret_user2[i]);
				break;
			}
			case 'c':
			{
				// 擦除数组3所在的扇区（使用数组1的起始地址）
				IapEraseSector(SECRET3_EEPROM_ADDR);
				// 写入数组3
				addr = SECRET3_EEPROM_ADDR;
				for (i = 0; i < SECRET3_LEN; i++) IapWriteByte(addr++, secret_user3[i]);
				break;
			}
		}		
}

//3.初始化写入，调用一次
// 在 usingeeprow.c 中添加
void Initialize_EEPROM()
{
		uint i;
    // 定义初始值
    uchar default1[SECRET1_LEN] = {'1', '1', '4', '5', '1', '4', '\0'}; // 密码1
    uchar default2[SECRET2_LEN] = {'1', '9', '1', '9', '8', '1', '\0'}; // 密码2
    uchar default3[SECRET3_LEN] = {'1', '2', '3', '4', '5', '6', '\0'}; // 密码3
    
    // 写入密码1
    IapEraseSector(SECRET1_EEPROM_ADDR);
    for (i = 0; i < SECRET1_LEN; i++) {
        IapWriteByte(SECRET1_EEPROM_ADDR + i, default1[i]);
    }
    
    // 写入密码2
    IapEraseSector(SECRET2_EEPROM_ADDR);
    for (i = 0; i < SECRET2_LEN; i++) {
        IapWriteByte(SECRET2_EEPROM_ADDR + i, default2[i]);
    }
    
    // 写入密码3
    IapEraseSector(SECRET3_EEPROM_ADDR);
    for (i = 0; i < SECRET3_LEN; i++) {
        IapWriteByte(SECRET3_EEPROM_ADDR + i, default3[i]);
    }
}
