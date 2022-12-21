/*
 * main.c

 *
 *  Created on: Dec 17, 2022
 *      Author: user
 */
#include <util/delay.h>
typedef unsigned char u8;
#define DDRA   *((volatile u8*)0x3A)
#define PORTA  *((volatile u8*)0x3B)
#define PINA   *((volatile u8*)0x39)

#define DDRB   *((volatile u8*)0x37)
#define PORTB  *((volatile u8*)0x38)
#define PINB   *((volatile u8*)0x36)
int main(void)
{
		DDRA &=~(1<<0);
		DDRA &=~(1<<1);
		PORTA |=(1<<0);
		PORTA |=(1<<1);

	    DDRB=0xff;
	   u8 seg_cthd[]={0x3F, 0x06, 0x5B,
			 0x4F, 0x66, 0x6D,
			 0x7D, 0x07, 0x7F,
			 0x6F};
	PORTB=0;
	u8 i=0;
	while(1)
	{
		if(((PINA>>0)&1)==0)
		{
			while (((PINA>>0)&1)==0)
			{
				_delay_ms(50);
				PORTB=seg_cthd[i];
			}
			if(i<9)
			{
			i++;
			}
		}
if(i>0)
{
		if(((PINA>>1)&1)==0&&i>0)
				{
			i--;
					while (((PINA>>1)&1)==0)
					{

						_delay_ms(50);
						PORTB=seg_cthd[i];
					}

				}
}
else
	i=0;
	}
	return 0;
}

