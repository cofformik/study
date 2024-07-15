#include"LCD.H"

void write_com(unsigned char com) //Ð´ÃüÁî
{
	RS_CLR;
	RW_CLR;
	P2=com;
	DelayMs(3);
	EN_SET;
	DelayMs(3);
	EN_CLR;
}

void write_data(unsigned char date)	 //Ð´Ò»¸ö×Ö·û
{
	RS_SET;
	RW_CLR;
	P2=date;
	DelayMs(3);
	EN_SET;
	DelayMs(3);
	EN_CLR;
}

void LCD_init()			//³õÊ¼»¯
{
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

/*------------------------------------------------ 
              Ð´Èë×Ö·û´®º¯Êý
------------------------------------------------*/
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
{     
 	if (y == 0) 
 	{     
	 	write_com(0x80 + x);     
 	}
 	else 
 	{     
 		write_com(0xC0 + x);     
 	}        
 	while (*s) 
 	{     
 		write_data( *s);     
 		s ++;     
 	}
}
