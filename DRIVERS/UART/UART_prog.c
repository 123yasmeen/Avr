/*
 * UART_prog.c
 *
 *  Created on: Jul 15, 2023
 *      Author: user
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "UART_priv.h"
#include "UART_config.h"

ES_t UART_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

#if SPEED_MODE==NORMAL
	UCSRA&=~(1<<1);
#elif SPEED_MODE==DOUBLE
	UCSRA|=(1<<1);
#else
#error "WRONG SPEED MODE"
#endif

#if UART_MODE ==TRANSMITTER
	UCSRB|=(1<<3);
#elif UART_MODE==RECIEVER
	UCSRB|=(1<<4);
#elif UART_MODE==TRANSCIEVER
	UCSRB|=(1<<3);
	UCSRB|=(1<<4);
#else
#error "WRONG UART MAODE"
#endif

	u8 Local_u8UCSRC=0;
#if DATA_LENGTH==FIVE_BIT
	Local_u8UCSRC&=~(1<<1);
	Local_u8UCSRC&=~(1<<2);
#elif DATA_LENGTH==SIX_BIT
	Local_u8UCSRC|=(1<<1);
	Local_u8UCSRC&=~(1<<2);
#elif DATA_LENGTH==SEVEN_BIT
	Local_u8UCSRC&=~(1<<1);
	Local_u8UCSRC|=(1<<2);
#elif DATA_LENGTH==EIGHT_BIT
	Local_u8UCSRC|=(1<<1);
	Local_u8UCSRC|=(1<<2);
#elif DATA_LENGTH==NINE_BIT
	Local_u8UCSRC|=(1<<1)
	Local_u8UCSRC|=(1<<2)
	UCSRB|=(1<<2);
#else
#error "WRONG DATA LENGTH"
#endif

#if PARITY_STATE==NO_PARITY
	Local_u8UCSRC&=~(1<<4);
	Local_u8UCSRC&=~(1<<5);
#elif PARITY_STATE==EVEN_PARITY
	Local_u8UCSRC&=~(1<<4);
	Local_u8UCSRC|=(1<<5);
#elif PARITY_STATE==ODD_PARITY
	Local_u8UCSRC|=(1<<4);
	Local_u8UCSRC|=(1<<5);
#else
#error "WRONG PARITY"
#endif

#if STOP_STATE==ONE_STOP_BIT
	Local_u8UCSRC&=~(1<<3);
#elif STOP_STATE==TWO_STOP_BIT
	Local_u8UCSRC|=(1<<3);
#else
#error "WRONG STOP STATE"
#endif

#if CLOCK_MODE==ASYCH
	Local_u8UCSRC&=~(1<<6);
#elif CLOCK_MODE==SYCH
	Local_u8UCSRC|=(1<<6);
#else
#error "WRONG CLOCK MODE"
#endif

	Local_u8UCSRC|=(1<<7);//to select UCSRC

	UCSRC=Local_u8UCSRC;

	u16 Local_u16UBRR=BAUDEQN(BAUD_RATE);

	UBRRL=(u8)Local_u16UBRR;
	UBRRH|=(Local_u16UBRR>>8);

	return Local_enuErrorState;
}

ES_t UART_enuSendChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	while(!((UCSRA>>UDRE)&1));
	UDR=Copy_u8Data;

	return Local_enuErrorState;
}

ES_t UART_enuRecieveChar(u8 *Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8Data!=NULL)
	{
	   while(!((UCSRA>>RXC)&1));
	   *Copy_u8Data=UDR;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t UART_enuSendString(const char* Copy_sData)
{
	ES_t Local_enuErrorState=ES_NOK;

	while(*Copy_sData!='\0')
	{
		while(!((UCSRA>>UDRE)&1));
		UDR=*Copy_sData;
		Copy_sData++;
	}

	return Local_enuErrorState;
}

ES_t UART_enuRecieveString(char* Copy_sData)
{
	ES_t Local_enuErrorState=ES_NOK;

	u8 Local_u8Data=0,Local_u8Index=0;
	while(1)
	{
		   while(!((UCSRA>>RXC)&1));
		   Local_u8Data=UDR;
		   if(Local_u8Data=='\r'||Local_u8Data=='\n')//enter
		   {
			   Copy_sData[Local_u8Index]='\0';
			   break;
		   }
		   else
		   {
			   Copy_sData[Local_u8Index]=Local_u8Data;
			   Local_u8Index++;
		   }
	}
	return Local_enuErrorState;
}
