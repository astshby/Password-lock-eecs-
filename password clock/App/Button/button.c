#include "button.h"	

//�������֣�ռ��P1
uchar button_is()
{	 
	
	//��λ�߼���0fʱ�����ж�λ��f0ʱ�����ж�λ��eg��f0ͬһ�а��º����Ϊ�͵�ƽ��0fͬ��
	uchar key=0;
	button_data=0x0f;
	if(button_data!=0x0f)
	{
		delay_us(100);   //��������
		if(button_data!=0x0f)
		{
			button_data=0x0f;
			switch(button_data)
			{
				case 0x07: key=1;break;
				case 0x0b: key=2;break;
				case 0x0d: key=3;break;
				case 0x0e: key=4;break;
			}
			button_data=0xf0;
			switch(button_data)//������Ϊ 0���������º�ļ�ֵ
			{
				case 0x70: key=key;break;
				case 0xb0: key=key+4;break;
				case 0xd0: key=key+8;break;
				case 0xe0: key=key+12;break;
			}
			while(button_data!=0xf0);//�ȴ������ɿ�
		}
	}
	else key=0;
	
	switch(key)
	{
		case 1:return '7';
		case 2:return '8';
		case 3:return '9';
		case 4:return 'a';
		case 5:return '4';
		case 6:return '5';
		case 7:return '6';
		case 8:return 'b';
		case 9:return '1';
		case 10:return '2';
		case 11:return '3';
		case 12:return 'c';
		case 13:return 'A';
		case 14:return '0';
		case 15:return 'B';
		case 16:return '%';
		default:return 0;
	}
}

	