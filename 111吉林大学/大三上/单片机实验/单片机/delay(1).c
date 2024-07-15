#include "delay.h"

void DelayUs2x(unsigned char t)
{   
 	while(--t);
}

void DelayMs(unsigned char t)
{
  	while(t--) 		//1mS
 	{
     	DelayUs2x(245);
 	}
}
