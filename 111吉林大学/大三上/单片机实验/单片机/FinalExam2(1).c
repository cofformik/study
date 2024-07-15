#include <REGX51.H>
#include<stdio.h>

#define uchar unsigned char 
#define uint unsigned int
	
#define THC0 0xf8
#define TLC0 0x50
#define THC1 0xFF
#define TLC1 0x9C
#define rol(value, bits) ((value << bits) | (value >> (sizeof(value)*8 - bits)))

#include "LCD.H"
#include "LED.H"
#include "delay.h"

uchar SSChaCode[]={'S','e','t','u','p',':',' ',' ',' ',' ',' ','r','/','m','i','n'};  //目标转速。 	   r/min
//uchar CSChaCode[]={'C','u','r',':',' ',' ',' ',' ',' ',' ',' ','r','/','m','i','n',' ',' ',' '};	   //实测转速:       r/min
uchar TAB_Y[] = {0XFF, 0XFF, 0XFF , 0XFF, 0XFF, 0XFF, 0XFF, 0XFF};
																												 

sbit S1=P3^6;
sbit S2=P3^7;

sbit MOTOR=P1^1;

uint SSpeed=74;
uint CurSpeed=0; //Current Speed

uint PCnt=0;//Pulse Count

int N=180;
int M=256;
int X=0;

void SetSpeed();
void delay(uchar x);
void LEDVt(uint CurSpeed);


void main()
{
	//InitialLCD
	LCD_init();
	SSChaCode[7]=SSpeed/1000+'0';
	SSChaCode[8]=SSpeed/100%10+'0';
	SSChaCode[9]=SSpeed/10%10+'0';
	SSChaCode[10]=SSpeed%10+'0';
	LCD_Write_String(0,0,SSChaCode);
	
	//InitialInterrupt
	//TMOD
	TMOD=0X11;    //t1 t2定时
	//TCON
	IT0=1;
	TR0=1;
	TR1=1;
	//TH0,TL0,TH1,TL1
	TH0=THC0;
	TL0=TLC0; 
	TH1=THC1;
	TL1=TLC1;
	//IntControl
	EA=1;
	ET1=1; //timer1
	ET0=1; //timer0
	EX0=1; //INT0
	
	while(1)
	{
		SendData(TAB_Y);
		//Set Speed
		SetSpeed();
		
	}
}

void SetSpeed()
{
	
	if(S1==0)
	{
		delay(50);
		if(S1==0)
		{
			SSpeed+=8;
			if(SSpeed>130) SSpeed=130;
			SSChaCode[7]=SSpeed/1000+'0';
			SSChaCode[8]=SSpeed/100%10+'0';
			SSChaCode[9]=SSpeed/10%10+'0';
			SSChaCode[10]=SSpeed%10+'0';
			LCD_Write_String(0,0,SSChaCode);
		}
	}
	if(S2==0)
	{
		delay(50);
		if(S2==0)
		{
			SSpeed-=8;
			if(SSpeed<50) SSpeed=50;
			SSChaCode[7]=SSpeed/1000+'0';
			SSChaCode[8]=SSpeed/100%10+'0';
			SSChaCode[9]=SSpeed/10%10+'0';
			SSChaCode[10]=SSpeed%10+'0';
			LCD_Write_String(0,0,SSChaCode);
		}
	}
}

void int0() interrupt 0
{
	PCnt++;
}

void t0() interrupt 1
{
	static unsigned int time=0;
	
	TH0=THC0;
	TL0=TLC0;
	
	time++;
	
	if(time>500)
	{
		CurSpeed=PCnt/6;	 //n=360
		time=0;
		PCnt=0;
		if(CurSpeed>SSpeed) N--;
		else if(CurSpeed<SSpeed) N++;
		LEDVt(CurSpeed);
	}
}

void timer_1()  interrupt 3
{
	TH1=THC1;
	TL1=TLC1; //0.1ms:65536-100=65436
	X+=N;
	if(X>M) {MOTOR=1;X-=M;}
	else MOTOR=0;
}

void LEDVt(uint CurSpeed)
{
	uint i;
	uint x;
	uchar cc=0XFE;
	
	if(CurSpeed<50) CurSpeed=50;
	x=(CurSpeed-50)/8;
	if(x>7) x=7;
	
	for(i=7;i>0;i--)
	{
		TAB_Y[i]=TAB_Y[i-1];
	}
	TAB_Y[0]=rol(cc,x);
}


void delay(uchar x)
{
	uint i,j;
	for(i=x;i>0;i--)
		for(j=50;j>0;j--);
}
 