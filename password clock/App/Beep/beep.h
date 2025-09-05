#ifndef _beep_H
#define _beep_H

#include "public.h"

sbit beep_data=P2^5;

void beep_voice(uint time);
void beep_start();
void beep_yes();
void beep_no();
void beep_paused();
void beep_change_start();
void beep_change_ok();
void beep_change_fin();

#endif