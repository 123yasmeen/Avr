/*
 * main.c

 *
 *  Created on: Dec 9, 2022
 *      Author: user
 */
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
typedef unsigned char u8;
#define DDRA *((volatile u8*)0x3B)
#define PORTA *((volatile u8*)0x3A)
int main (void){

	DDRA|=(1<<0);
	while(1)
	{
		PORTA|=(1<<0);
		_delay_ms(1000);
		PORTA&=~(1<<0);
		_delay_ms(1000);

	}
	return 0;
}

