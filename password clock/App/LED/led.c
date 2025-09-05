#include "led.h"
uchar record[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

void decode3_8(unsigned char i) 
{
    pin2=i&0x01;       
    pin3=(i>>1)&0x01; 
    pin4=(i>>2)&0x01;
	return; 
}

void led_show(uchar *str)
{
	uchar i=6;
	while(*str!='\0')
	{
		led_data=0x00;      //消除伪影，前后都要消除
		decode3_8(i--);
		led_data=record[*str-'0'];
		delay_ms(1);
		str++;	
	}
	while(i>0)
	{
		led_data=0x00;
		decode3_8(i--);
		led_data=record[10];
		delay_ms(1);
	}
	led_data=0x00;
	return ;
}

void led_paused()
{
	uchar i=1;
	uint time=paused_time;
	if(time==0)
	{
		led_data=0x00;
		decode3_8(1);
		led_data=record[0];
		delay_ms(1);
		led_data=0x00;
		return ;
	}
	while(time)
	{
		led_data=0x00;
		decode3_8(i++);
		led_data=record[time%10];
		time=time/10;
		delay_ms(2);	
	}
	led_data=0x00;
	return ;	
}

void num()
{
	uint kks=0;
	if (now_str_loc < 6) 
	{ 
		now_str[now_str_loc++]=now;
		now_str[now_str_loc]='\0'; 	//添加终止符
	} 
	else 
	{
		while(kks<5)
		{
			now_str[kks]=now_str[kks+1];
			kks++;
		}
		now_str[kks]=now;
		now_str[now_str_loc]='\0';
	}
	return ;
}

void del()
{
	if(now_str_loc>0)
	{
		now_str_loc--;
		now_str[now_str_loc]='\0';
	}
	else return;
	return;
}

void change_num()
{
	uint kks=0;
	if (change_str_loc < 6) 
	{ 
		change_str[change_str_loc++]=change;
		change_str[change_str_loc]='\0'; 	//添加终止符
	} 
	else 
	{
		while(kks<5)
		{
			change_str[kks]=change_str[kks+1];
			kks++;
		}
		change_str[kks]=change;
		change_str[change_str_loc]='\0';
	}
	return ;
}

void change_del()
{
	if(change_str_loc>0)
	{
		change_str_loc--;
		change_str[change_str_loc]='\0';
	}
	else return;
	return;
}
