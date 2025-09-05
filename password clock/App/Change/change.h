#ifndef _change_H
#define _change_H

#include "public.h"
#include "change.h"  
#include "paused.h"
#include "button.h"
#include "led.h"
#include "lcd1602.h"
#include "beep.h"
#include "motor.h"
#include "usingeeprow.h"

void check();
void change_secret(uchar secret_code);

#endif
