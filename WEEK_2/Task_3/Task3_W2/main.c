/*
 * main.c

 *
 *  Created on: Dec 21, 2022
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
	 u8 seg_cthd[]={0x3F, 0x06, 0x5B,
				 0x4F, 0x66, 0x6D,
				 0x7D, 0x07, 0x7F,
				 0x6F};
	 DDRA=0xff;
	 DDRB|=(1<<0);//A
	 DDRB|=(1<<1);//B
	 PORTB&=~(1<<0);
	 PORTB&=~(1<<1);

	 DDRB&=~(1<<2);//increment
	 DDRB&=~(1<<3);//decrement
	 PORTB|=(1<<2);
	 PORTB|=(1<<3);
	 u8 i=50;
	while(1)
	{
		PORTB |=(1<<1);
				PORTA=seg_cthd[i%10];
				PORTB &=~(1<<0);
				_delay_ms(10);
				PORTB |=(1<<0);
				PORTA=seg_cthd[i/10];
				PORTB &=~(1<<1);
				_delay_ms(10);
		if(((PINB>>2)&1)==0)
				{
					while (((PINB>>2)&1)==0)
					{
						PORTB |=(1<<1);
								PORTA=seg_cthd[i%10];
							    PORTB &=~(1<<0);
								_delay_ms(10);
								PORTB |=(1<<0);
								PORTA=seg_cthd[i/10];
								PORTB &=~(1<<1);
								_delay_ms(10);

					}
					i++;
				}
		if(i>0)
		{
				if(((PINB>>3)&1)==0&&i>0)
						{
					i--;
							while (((PINB>>3)&1)==0)
							{
								PORTB |=(1<<1);
								PORTA=seg_cthd[i%10];
								PORTB &=~(1<<0);
								_delay_ms(10);
								PORTB |=(1<<0);
								PORTA=seg_cthd[i/10];
								PORTB &=~(1<<1);
								_delay_ms(10);

							}

						}
		}

	}
	return 0;
}

