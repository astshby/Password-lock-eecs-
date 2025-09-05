#include "change.h"

bit compare(uchar *temp1)
{
	uchar* temp2=now_str;
	while(*temp1 && *temp2 && (*temp1==*temp2))
	{
		temp1++;
		temp2++;
	}
	return (*temp1=='\0' && *temp2=='\0');
}

void check()
{
	check_flag++;
	if(check_flag<5)    
	{
		if(compare(secret_user1))
		{
			check_flag=0;
			beep_yes();
			lcd1602_welcome(1);
			motor_using(3000);
			del();del();del();del();del();del();
		}
		else if(compare(secret_user2))
		{
			check_flag=0;
			beep_yes();
			lcd1602_welcome(2);
			motor_using(3000);
			del();del();del();del();del();del();
		}
		else if(compare(secret_user3))
		{
			check_flag=0;
			beep_yes();
			lcd1602_welcome(3);
			motor_using(3000);
			del();del();del();del();del();del();
		}
		else
		{
			beep_no();
			lcd1602_away();
			del();del();del();del();del();del();
			
		}		
	}
	else
	{
		beep_paused();
		lcd1602_bakabaka();
		del();del();del();del();del();del();
		
		paused_start();

		check_flag=0;
	}
}	

bit change_check(uchar secret_code)
{
	bit ans;
	switch(secret_code)
	{
		case 'a':ans=compare(secret_user1);break;
		case 'b':ans=compare(secret_user2);break;
		case 'c':ans=compare(secret_user3);break;
		default:ans=0;
		return ans;
	}
}
void last_change(uchar *new_str,uchar *past_str,uchar secret_code)
{
	while((*past_str++ = *new_str++));      //可能会有多的东西读入
	Arrays_SaveToEEPROM(secret_code);
	
	change_del();change_del();change_del();change_del();change_del();change_del();
	beep_change_fin();
	lcd1602_change_fin(secret_code);
}	

void change_secret(uchar secret_code)
{
	motor_stop();
	del();del();del();del();del();del();
	beep_change_start();
	lcd1602_change_before(secret_code);
	
	while(1)
	{
		motor_stop();
		
		if(paused_finish_flag)
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
				else if(now=='B') 
				{
					bit ans=change_check(secret_code);
					if(ans) 
					{
						del();del();del();del();del();del();
						break;
					}
					else 
					{
						check_flag++;
						
						if(check_flag<5)
						{
							beep_no();
							lcd1602_change_away(secret_code);
							del();del();del();del();del();del();
						}
						else
						{
							beep_paused();
							lcd1602_bakabaka();
							del();del();del();del();del();del();
							paused_start();
							check_flag=0;
						}
					}
				}
				else if(now>='a' && now<='c')
				{
					del();del();del();del();del();del();
					beep_change_start();
					lcd1602_change_stop(secret_code);
					return;
				}
			}
		}
		else
		{
			if(!paused_finish_flag) led_paused();
			else
			{
				motor_stop();
				beep_start();
				lcd1602_change_restart(secret_code);
				paused_finish_flag=0;
			}	
		}
	}

	motor_stop();
	beep_change_ok();
	lcd1602_change_ok(secret_code);
	while(1)
	{
		motor_stop();
		led_show(change_str);
		change=button_is();
		if(change!=0)
		{
			if(change>='0' && change<='9') change_num();
			else if(change=='A') change_del();
			else if(change>='a' && change<='c')
			{
				change_del();change_del();change_del();change_del();change_del();change_del();
				beep_change_start();
				lcd1602_change_stop(secret_code);
				return;
			}
			else if(change=='%' && change_str_loc>0)
			{
				switch(secret_code)
				{
					case 'a':last_change(change_str,secret_user1,secret_code);return ;
					case 'b':last_change(change_str,secret_user2,secret_code);return ;
					case 'c':last_change(change_str,secret_user3,secret_code);return ;
				}
			}
		}
	}
}