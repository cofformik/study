#ifndef __LCD_H__
#define __LCD_H__

#include <REGX51.H>
#include<intrins.h>
#include"delay.h"

//sbit RS = P2^0; 
//sbit RW = P2^1;
//sbit EN = P2^2;

sbit RS = P3^3;   //¶¨Òå¶Ë¿Ú 
sbit RW = P3^4;
sbit EN = P3^5;

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1

#define EN_CLR EN=0
#define EN_SET EN=1


void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data);
void LCD_init();
void write_com(unsigned char com);
void write_data(unsigned char date);

#endif
