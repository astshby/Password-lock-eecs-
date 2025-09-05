#ifndef _motor_H
#define _motor_H

#include "public.h"

sbit DC_data=P1^1;

void motor_stop();
void motor_using(uint time);

#endif