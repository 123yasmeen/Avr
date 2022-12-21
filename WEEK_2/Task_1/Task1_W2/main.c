/*
 * main.c
 *
 *  Created on: Dec 17, 2022
 *      Author: user
 */
typedef unsigned char u8;
#define DDRA   *((volatile u8*)0x3B)
#define PORTA  *((volatile u8*)0x3A)
#define PINA   *((volatile u8*)0x39)

#define DDRB   *((volatile u8*)0x37)
#define PORTB  *((volatile u8*)0x38)
#define PINB   *((volatile u8*)0x36)
int main (void)
{
	DDRA|=(1<<0);
	DDRA|=(1<<1);
	PORTA&=~(1<<0);
	PORTA&=~(1<<1);

	DDRB&=~(1<<0);
	DDRB&=~(1<<1);
	DDRB&=~(1<<2);
	//pull up resistor
	PORTB|=(1<<0);
	PORTB|=(1<<1);
	PORTB|=(1<<2);
	while(1)
	{
		if(((PINB>>0)&1)==0)
		{
			PORTA|=(1<<0);
		}
		else if(((PINB>>1)&1)==0)
		{
			PORTA|=(1<<1);
		}
		else if(((PINB>>2)&1)==0)
		{
			PORTA|=(1<<0);
			PORTA|=(1<<1);
		}
		else
		{
			PORTA&=~(1<<0);
			PORTA&=~(1<<1);
		}
	}
	return 0;
}

