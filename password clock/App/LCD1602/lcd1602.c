#include "lcd1602.h"

//写命令
void lcd1602_write_cmd(uchar cmd)
{
	LCD1602_RS=0;//选择命令
	LCD1602_RW=0;//选择写
	LCD1602_E=0;
	LCD1602_data=cmd;//准备命令
	delay_ms(1);
	LCD1602_E=1;//使能脚E先上升沿写入
	delay_ms(1);
	LCD1602_E=0;//使能脚E后负跳变完成写入	
}

//写数据
void lcd1602_write_data(uchar dat) 
{
	LCD1602_RS=1;//选择数据
	LCD1602_RW=0;//选择写
	LCD1602_E=0;
	LCD1602_data=dat;//准备数据
	delay_ms(1);
	LCD1602_E=1;//使能脚E先上升沿写入
	delay_ms(1);
	LCD1602_E=0;//使能脚E后负跳变完成写入		
}

//清屏
void lcd1602_clear()
{
	lcd1602_write_cmd(0x01);	
}
//初始化
void lcd1602_init()
{
	lcd1602_write_cmd(0x38);//数据总线8位，显示2行，5*7点阵/字符
	lcd1602_write_cmd(0x0c);//显示功能开，无光标，光标闪烁
	lcd1602_write_cmd(0x06);//写入新数据后光标右移，显示屏不移动
	lcd1602_clear();//清屏	
}

//断电与唤醒
void lcd1602_stop()
{
	lcd1602_write_cmd(0x08); 
}
void lcd1602_wake()
{
	lcd1602_write_cmd(0x0C);
}

//显示函数
void lcd1602_show(uchar x,uchar y,uchar *str)
{
	uchar i=0;

	if(y>1||x>15)return;//行列参数不对则强制退出

	if(y<1)	//第1行显示
	{	
		while(*str!='\0')//字符串是以'\0'结尾，只要前面有内容就显示
		{
			if(i<16-x)//如果字符长度超过第一行显示范围，则在第二行继续显示
			{
				lcd1602_write_cmd(0x80+i+x);//第一行显示地址设置	
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16);//第二行显示地址设置	
			}
			lcd1602_write_data(*str);//显示内容
			str++;//指针递增
			i++;	
		}	
	}
	else	//第2行显示
	{
		while(*str!='\0')
		{
			if(i<16-x) //如果字符长度超过第二行显示范围，则在第一行继续显示
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


//实际功能
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
	lcd1602_clear();   //不清屏幕，多余显示
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
	lcd1602_show(0,0,"Wrong：");
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
	lcd1602_show(0,0,"Restart change：");
	lcd1602_show(0,1,kks);
	delay_ms(1500);
	lcd1602_clear();   
	lcd1602_stop();	
}