#include "public.h"

void delay_us(uint ten_us)
{
	while(ten_us--);	
}

void delay_ms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}