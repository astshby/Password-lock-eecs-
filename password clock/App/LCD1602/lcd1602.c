#include "lcd1602.h"

//д����
void lcd1602_write_cmd(uchar cmd)
{
	LCD1602_RS=0;//ѡ������
	LCD1602_RW=0;//ѡ��д
	LCD1602_E=0;
	LCD1602_data=cmd;//׼������
	delay_ms(1);
	LCD1602_E=1;//ʹ�ܽ�E��������д��
	delay_ms(1);
	LCD1602_E=0;//ʹ�ܽ�E���������д��	
}

//д����
void lcd1602_write_data(uchar dat) 
{
	LCD1602_RS=1;//ѡ������
	LCD1602_RW=0;//ѡ��д
	LCD1602_E=0;
	LCD1602_data=dat;//׼������
	delay_ms(1);
	LCD1602_E=1;//ʹ�ܽ�E��������д��
	delay_ms(1);
	LCD1602_E=0;//ʹ�ܽ�E���������д��		
}

//����
void lcd1602_clear()
{
	lcd1602_write_cmd(0x01);	
}
//��ʼ��
void lcd1602_init()
{
	lcd1602_write_cmd(0x38);//��������8λ����ʾ2�У�5*7����/�ַ�
	lcd1602_write_cmd(0x0c);//��ʾ���ܿ����޹�꣬�����˸
	lcd1602_write_cmd(0x06);//д�������ݺ������ƣ���ʾ�����ƶ�
	lcd1602_clear();//����	
}

//�ϵ��뻽��
void lcd1602_stop()
{
	lcd1602_write_cmd(0x08); 
}
void lcd1602_wake()
{
	lcd1602_write_cmd(0x0C);
}

//��ʾ����
void lcd1602_show(uchar x,uchar y,uchar *str)
{
	uchar i=0;

	if(y>1||x>15)return;//���в���������ǿ���˳�

	if(y<1)	//��1����ʾ
	{	
		while(*str!='\0')//�ַ�������'\0'��β��ֻҪǰ�������ݾ���ʾ
		{
			if(i<16-x)//����ַ����ȳ�����һ����ʾ��Χ�����ڵڶ��м�����ʾ
			{
				lcd1602_write_cmd(0x80+i+x);//��һ����ʾ��ַ����	
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16);//�ڶ�����ʾ��ַ����	
			}
			lcd1602_write_data(*str);//��ʾ����
			str++;//ָ�����
			i++;	
		}	
	}
	else	//��2����ʾ
	{
		while(*str!='\0')
		{
			if(i<16-x) //����ַ����ȳ����ڶ�����ʾ��Χ�����ڵ�һ�м�����ʾ
			{
				lcd1602_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd1602_write_cmd(0x80+i+x-16);	
			}
			lcd1602_write_data(*str);
			str++;
			i++;	
		}	
	}				
}


//ʵ�ʹ���
void lcd1602_hello()
{
	lcd1602_init();
	lcd1602_show(0,0,"Hello!");
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_welcome(uint i)
{
	uchar kks[6]="User0";
	kks[4]=i+'0';
	lcd1602_wake();
	lcd1602_show(0,0,kks);
	lcd1602_show(0,1,"Welcome!");
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_away()
{
	lcd1602_wake();
	lcd1602_show(0,0,"Wrong!");
	switch(check_flag)
	{
		case 1:lcd1602_show(0,1,"Rest 4 times!");break;
		case 2:lcd1602_show(0,1,"Rest 3 times!");break;
		case 3:lcd1602_show(0,1,"Rest 2 times!");break;
		case 4:lcd1602_show(0,1,"Rest 1 time!");break;
	}
	delay_ms(1500);
	lcd1602_clear();   //������Ļ��������ʾ
	lcd1602_stop();	
}

void lcd1602_bakabaka()
{
	lcd1602_wake();
	lcd1602_show(0,0,"baka or thief?");
	lcd1602_show(0,1,"Waiting 1 min!");
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_restart()
{
	lcd1602_wake();
	lcd1602_show(0,0,"Restart!");
	lcd1602_show(0,1,"Never again baka");
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_change_before(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"Need:");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_change_ok(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"OK to change:");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_change_stop(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"Stop change:");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_change_fin(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"Success change:");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();
	lcd1602_stop();
}

void lcd1602_change_away(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"Wrong��");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();
	switch(check_flag)
	{
		case 1:lcd1602_show(0,0,"Rest 4 times!");break;
		case 2:lcd1602_show(0,0,"Rest 3 times!");break;
		case 3:lcd1602_show(0,0,"Rest 2 times!");break;
		case 4:lcd1602_show(0,0,"Rest 1 time!");break;
	}
	delay_ms(1500);
	lcd1602_clear();   
	lcd1602_stop();	
}

void lcd1602_change_restart(uchar secret_code)
{
	uchar kks[13]="User0 secret";
	kks[4]=secret_code-'a'+1+'0';
	lcd1602_wake();
	lcd1602_show(0,0,"Restart change��");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();   
	lcd1602_stop();	
}