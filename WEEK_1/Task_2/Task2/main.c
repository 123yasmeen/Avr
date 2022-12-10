/*
 * main.c

 *
 *  Created on: Dec 10, 2022
 *      Author: user
 */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
typedef unsigned char u8;
#define DDRA *((volatile u8*)0x3B)
#define PORTA *((volatile u8*)0x3A)
int main (void)
{
	DDRA|=(1<<0);
	DDRA|=(1<<1);
	DDRA|=(1<<2);
	DDRA|=(1<<3);
	DDRA|=(1<<4);
	DDRA|=(1<<5);
	DDRA|=(1<<6);
	while(1)
	{
		PORTA|=(1<<0);
		PORTA|=(1<<6);
		_delay_ms(500);
		PORTA|=(1<<1);
		PORTA|=(1<<5);
		_delay_ms(500);
		PORTA|=(1<<2);
		PORTA|=(1<<4);
		_delay_ms(500);
		PORTA|=(1<<3);
		_delay_ms(500);
		PORTA&=~(1<<3);
		_delay_ms(500);
		PORTA&=~(1<<2);
		PORTA&=~(1<<4);
		_delay_ms(500);
		PORTA&=~(1<<1);
		PORTA&=~(1<<5);
		_delay_ms(500);
		PORTA&=~(1<<0);
		PORTA&=~(1<<6);
		_delay_ms(500);
	}
	return 0;
}
