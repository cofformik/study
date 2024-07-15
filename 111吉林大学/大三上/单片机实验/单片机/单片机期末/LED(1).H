#ifndef __LED_H__
#define __LED_H__

#include <REGX51.H>
#include<intrins.h>
#include"delay.h"


sbit DATA_X = P0^0;
sbit CLK_X = P0^1;
sbit WR_X = P0^2;
sbit EN_X = P0^7;

sbit DATA_Y = P0^3;
sbit CLK_Y = P0^5;
sbit WR_Y = P0^6;
sbit EN_Y = P0^4;


void SendByte(unsigned char x,unsigned char dat);
void SendData(unsigned char *s);

#endif
