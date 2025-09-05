#include "usingeeprow.h"

//ע�⿴�ĵ����ڸ����ڵĶ���
/* �ر�IAP���� */
void IapIdle()
{
    IAP_CONTR = 0;    // �ر�IAP����
    IAP_CMD = 0;      // �������Ĵ���
    IAP_TRIG = 0;     // ��������Ĵ���
    IAP_ADDRH = 0xFF; // ����ַָ���EEPROM���򣬷�ֹ�����
    IAP_ADDRL = 0xFF;
}

/* ��EEPROM�ֽڶ�ȡ */
uchar IapReadByte(uint addr)
{
    uchar dat; // �洢����������

    IAP_CONTR = ENABLE_IAP;        // ʹ��IAP
    IAP_CMD = IAP_READ;            // ���ö�����
    IAP_ADDRL = addr;              // ����Ŀ���ַ��8λ
    IAP_ADDRH = addr >> 8;          // ����Ŀ���ַ��8λ

    // �������� (��д0x5A, ��д0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // �ȴ��������
    _nop_();

    dat = IAP_DATA;                // ��ȡ����
    IapIdle();                     // �ر�IAP

    return dat;
}

/* ��EEPROM�ֽ�д�� */
void IapWriteByte(uint addr, uchar dat)
{
    IAP_CONTR = ENABLE_IAP;        // ʹ��IAP
    IAP_CMD = IAP_WRITE;           // ����д����
    IAP_ADDRL = addr;              // ����Ŀ���ַ��8λ
    IAP_ADDRH = addr >> 8;          // ����Ŀ���ַ��8λ
    IAP_DATA = dat;                // ׼��Ҫд�������

    // �������� (��д0x5A, ��д0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // �ȴ��������
    _nop_();

    IapIdle();                     // �ر�IAP
}

/* ����EEPROM���� */
void IapEraseSector(uint addr)
{
    // ע�⣺����������������������ģ�addrֻ�����ڸ������ڼ��ɡ�
    IAP_CONTR = ENABLE_IAP;        // ʹ��IAP
    IAP_CMD = IAP_ERASE;           // ���ò�������
    IAP_ADDRL = addr;              // ����������ַ��8λ����ַֻ���������ڼ��ɣ�
    IAP_ADDRH = addr >> 8;          // ����������ַ��8λ

    // �������� (��д0x5A, ��д0xA5)
    IAP_TRIG = 0x46;
    IAP_TRIG = 0xB9;
    _nop_();                       // �ȴ�������ɣ�����ʱ��ϳ���
    _nop_();

    IapIdle();                     // �ر�IAP
}

//���ܺ���
//  ��EEPROM��ȡ�������鵽RAM
void Arrays_LoadFromEEPROM()
{
    uint i;
    uint addr;

    // ��ȡ����1
    addr = SECRET1_EEPROM_ADDR;
    for (i = 0; i < SECRET1_LEN; i++) {
        secret_user1[i] = IapReadByte(addr++);
    }

    // ��ȡ����2
    addr = SECRET2_EEPROM_ADDR;
    for (i = 0; i < SECRET2_LEN; i++) {
        secret_user2[i] = IapReadByte(addr++);
    }

    // ��ȡ����3
    addr = SECRET3_EEPROM_ADDR;
    for (i = 0; i < SECRET3_LEN; i++) {
        secret_user3[i] = IapReadByte(addr++);
    }
}

// 2. �����������RAMд��EEPROM
void Arrays_SaveToEEPROM(uchar secret_code)
{
    uint i;
    uint addr;

    // **��Ҫ��STC��EEPROMд��ǰ�����Ȳ�������������**
    // ��������1��2��3λ�ڲ�ͬ����������������Ҫ�������ǹ�ͬ���ڵ�������
    // ����Ϊ�˼򵥣����ǲ���ÿ���������ڵ�����������
    // ע�⣺�������������������ͨ����512�ֽڣ���������ȷ��������ݲ��ֲ�����˶�ʧ�������ݡ�
		
		switch(secret_code)
		{
			case 'a':
			{
				// ��������1���ڵ�������ʹ������1����ʼ��ַ��
				IapEraseSector(SECRET1_EEPROM_ADDR);
				// д������1
				addr = SECRET1_EEPROM_ADDR;
				for (i = 0; i < SECRET1_LEN; i++) IapWriteByte(addr++, secret_user1[i]);
				break;
			}
			case 'b':
			{
				// ��������2���ڵ�������ʹ������1����ʼ��ַ��
				IapEraseSector(SECRET2_EEPROM_ADDR);
				// д������2
				addr = SECRET2_EEPROM_ADDR;
				for (i = 0; i < SECRET2_LEN; i++) IapWriteByte(addr++, secret_user2[i]);
				break;
			}
			case 'c':
			{
				// ��������3���ڵ�������ʹ������1����ʼ��ַ��
				IapEraseSector(SECRET3_EEPROM_ADDR);
				// д������3
				addr = SECRET3_EEPROM_ADDR;
				for (i = 0; i < SECRET3_LEN; i++) IapWriteByte(addr++, secret_user3[i]);
				break;
			}
		}		
}

//3.��ʼ��д�룬����һ��
// �� usingeeprow.c �����
void Initialize_EEPROM()
{
		uint i;
    // �����ʼֵ
    uchar default1[SECRET1_LEN] = {'1', '1', '4', '5', '1', '4', '\0'}; // ����1
    uchar default2[SECRET2_LEN] = {'1', '9', '1', '9', '8', '1', '\0'}; // ����2
    uchar default3[SECRET3_LEN] = {'1', '2', '3', '4', '5', '6', '\0'}; // ����3
    
    // д������1
    IapEraseSector(SECRET1_EEPROM_ADDR);
    for (i = 0; i < SECRET1_LEN; i++) {
        IapWriteByte(SECRET1_EEPROM_ADDR + i, default1[i]);
    }
    
    // д������2
    IapEraseSector(SECRET2_EEPROM_ADDR);
    for (i = 0; i < SECRET2_LEN; i++) {
        IapWriteByte(SECRET2_EEPROM_ADDR + i, default2[i]);
    }
    
    // д������3
    IapEraseSector(SECRET3_EEPROM_ADDR);
    for (i = 0; i < SECRET3_LEN; i++) {
        IapWriteByte(SECRET3_EEPROM_ADDR + i, default3[i]);
    }
}
