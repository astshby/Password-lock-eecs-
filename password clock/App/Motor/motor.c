#include "motor.h"

void motor_stop()
{
	DC_data=0;
}

void motor_using(uint time)
{
	DC_data=1;
	delay_ms(time);
	DC_data=0;
}//可能与lcd有冲突