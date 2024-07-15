#include"LED.H"

unsigned char code TAB_X[] = {0x80, 0X40, 0X20 , 0X10, 0X08, 0X04, 0X02, 0X01};

void SendByte(unsigned char x, unsigned char dat)
{
	unsigned char a;
	//x=0,control x; x=1,control y
	if(x==0){
		EN_X=1;
		CLK_X=0;
		WR_X=0;
		for(a=0;a<8;a++)
		{
			DATA_X=dat>>7;
			dat<<=1;
			CLK_X=1;
			CLK_X=0;    
		}
		WR_X=1;
		WR_X=0;
		EN_X=0;
	}else{
		EN_Y=1;
		CLK_Y=0;
		WR_Y=0;
		for(a=0;a<8;a++)
		{
			DATA_Y=dat>>7;
			dat<<=1;
			CLK_Y=1;
			CLK_Y=0;
		}
		WR_Y=1;
		WR_Y=0;
		EN_Y=0;
	}
}


void SendData(unsigned char *s)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		SendByte(0,TAB_X[i]);
		SendByte(1,s[i]);
		DelayMs(2);
	}
}