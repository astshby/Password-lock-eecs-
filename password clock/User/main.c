#include "public.h" //�Լ���һ���á���
#include "globals.h"
#include "change.h"   
#include "paused.h"
#include "button.h"
#include "led.h"
#include "lcd1602.h"
#include "beep.h"
#include "motor.h"
#include "usingeeprow.h"

uchar secret_user1[7]={0};
uchar secret_user2[7]={0};
uchar secret_user3[7]={0};

uchar now_str[7]={0};
uint now_str_loc=0;
uchar now;

uchar check_flag=0;
uchar paused_flag=0;
uint paused_time=60;
bit paused_finish_flag=0;

uchar change_str[7]={0};
uint change_str_loc=0;
uchar change;

void main()
{
	motor_stop();
	beep_start();
	lcd1602_hello();
	
	if (IapReadByte(INIT_FLAG_ADDR) != 0x5A)
	{			
    Initialize_EEPROM();        // ����ʼ����־
    IapWriteByte(INIT_FLAG_ADDR, 0x5A); // ���ñ�־λ
  }//��ʼ����������һ��
	Arrays_LoadFromEEPROM(); //��eeprow������д��raw
	
	while(1)
	{
		motor_stop();
		
		if(paused_finish_flag)    //��ǰ�жϣ���ֹ�жϺ�������ʱʧ��
		{
			beep_start();
			lcd1602_restart();
			paused_finish_flag=0;
		}
		
		if(!paused_flag)
		{	
			led_show(now_str);
			now=button_is();
			if(now!=0)
			{
				if(now>='0' && now<='9') num();
				else if(now=='A') del();
				else if(now=='B') check();
				else if(now>='a' && now<='c') change_secret(now);
			}
		}
		else led_paused();		
	}	
}
