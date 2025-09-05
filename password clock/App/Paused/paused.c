#include "change.h"

uint count_200us;
uint count_50ms;

void paused_start()
{
	count_200us=0;   
	count_50ms=0;
	LED_paused=1;
	IE=0x82;
	TMOD=0x02;
	TCON=0x10;
	TL0=0x48;
	TH0=0x48;  //¼ÇÂ¼200us
	paused_flag=1;
}
void paused_stop()
{
	LED_paused=0;
	TH0=0x00;
	TL0=0x00;
	TCON=0x00;
	TMOD=0x00;
	IE=0x00;
	paused_time=60;
	paused_flag=0;
} 

void paused_min() interrupt 1
{
	if(paused_time==0)
	{
		led_paused();
		paused_stop();
		paused_finish_flag=1;
		return ;
	}
	
	count_200us++;
	
	if(count_200us==250)
	{
		count_200us=0;
		count_50ms++;
		
		if(count_50ms==20)
		{
			count_50ms=0;
			LED_paused=~LED_paused;
			paused_time--;
		}
	}
}
	