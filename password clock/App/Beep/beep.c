#include "beep.h"

//·äÃùÆ÷Âö³åÃù½Ğ1ms
void beep_voice(uint time)
{
	beep_data=0;
	while(time--)
	{
		beep_data=!beep_data;
		delay_ms(1);
	}
}

void beep_start()
{
	uint i=3;
	while(i--)
	{
		beep_voice(200);
		delay_ms(100);
	}
	beep_data=1;
}
void beep_yes()
{
	beep_voice(800);
	delay_ms(100);
	beep_data=1;
}
void beep_no()
{
	uint i=2;
	while(i--)
	{
		beep_voice(250);
		delay_ms(100);
	}
	beep_data=1;
}

void beep_paused()
{
	uint i=4;
	while(i--)
	{
		beep_voice(250);
		delay_ms(100);
	}
	beep_data=1;
}

void beep_change_start()
{
	beep_voice(200);
	delay_ms(50);
	beep_data=1;
}
void beep_change_ok()
{
	beep_voice(400);
	delay_ms(50);
	beep_data=1;
}
void beep_change_fin()
{
	uint i=5;
	while(i--)
	{
		beep_voice(100);
		delay_ms(50);
	}
	beep_data=1;
}