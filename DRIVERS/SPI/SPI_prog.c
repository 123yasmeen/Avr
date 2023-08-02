/*
 * SPI_prog.c
 *
 *  Created on: Jul 17, 2023
 *      Author: user
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"

#include "SPI_priv.h"
#include "SPI_config.h"



ES_t SPI_enuInitMasterMode(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//MOSI -->master output
	DIO_enuSetPinDirection(MOSI_PORT,MOSI_PIN,DIO_u8OUTPUT);
	//MISO -->master input
	DIO_enuSetPinDirection(MISO_PORT,MISO_PIN,DIO_u8INPUT);
	//CLK -->output
	DIO_enuSetPinDirection(CLK_PORT,CLK_PIN,DIO_u8OUTPUT);

	//enable SPI
	SPCR|=(1<<6);

	//check data order
#if DATA_ORDER==LSB
	SPCR|=(1<<5);
#elif DATA_ORDER==MSB
	SPCR&=~(1<<5);
#else
#error "WRONG DATA ORDER"
#endif

	//select master mode
	SPCR|=(1<<4);

	//Check Clock polarity
#if CLOCK_POLARITY==HIGH
	SPCR|=(1<<3);
#elif CLOCK_POLARITY==LOW
	SPCR&=~(1<<3);
#else
#error "WRONG CLOCK POLARITY"
#endif

	//Check Clock phase
#if CLOCK_PHASE==SAMPLE_LEADING
	SPCR&=~(1<<2);
#elif CLOCK_PHASE==SETUP_LEADING
	SPCR|=(1<<2);
#else
#error "WRONG CLOCK PHASE"
#endif

	//Check Clock rate
#if CLOCK_RATE==(1/4)
	SPCR&=~(1<<1);
	SPCR&=~(1<<0);
#elif CLOCK_RATE==(1/16)
	SPCR&=~(1<<1);
	SPCR|=(1<<0);
#elif CLOCK_RATE==(1/64)
	SPCR|=(1<<1);
	SPCR&=~(1<<0);
#elif CLOCK_RATE==(1/128)
	SPCR|=(1<<1);
	SPCR|=(1<<0);
#else
#error "WRONG CLOCK RATE"
#endif

	//Double SPI mode
#if DOUBLE_SPI_SPEED==ENABLED
	SPSR|=(1<<0);
#elif DOUBLE_SPI_SPEED==DISABLED
	SPSR&=~(1<<0);
#else
#error "WRONG INPUT"
#endif

	return Local_enuErrorState;
}

ES_t SPI_enuInitSlaveMode(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//MOSI -->slave input
	DIO_enuSetPinDirection(MOSI_PORT,MOSI_PIN,DIO_u8INPUT);
	//MISO -->slave output
	DIO_enuSetPinDirection(MISO_PORT,MISO_PIN,DIO_u8OUTPUT);
	//CLK -->input
	DIO_enuSetPinDirection(CLK_PORT,CLK_PIN,DIO_u8INPUT);
	//SS -->input
	DIO_enuSetPinDirection(SS_PORT,SS_PIN,DIO_u8INPUT);

	//enable SPI
	SPCR|=(1<<6);

	//check data order
#if DATA_ORDER==LSB
	SPCR|=(1<<5);
#elif DATA_ORDER==MSB
	SPCR&=~(1<<5);
#else
#error "WRONG DATA ORDER"
#endif

	//select Slave mode
	SPCR&=~(1<<4);

	//Check Clock polarity
#if CLOCK_POLARITY==HIGH
	SPCR|=(1<<3);
#elif CLOCK_POLARITY==LOW
	SPCR&=~(1<<3);
#else
#error "WRONG CLOCK POLARITY"
#endif

	//Check Clock phase
#if CLOCK_PHASE==SAMPLE_LEADING
	SPCR&=~(1<<2);
#elif CLOCK_PHASE==SETUP_LEADING
	SPCR|=(1<<2);
#else
#error "WRONG CLOCK PHASE"
#endif

	//Check Clock rate
#if CLOCK_RATE==(1/4)
	SPCR&=~(1<<1);
	SPCR&=~(1<<0);
#elif CLOCK_RATE==(1/16)
	SPCR&=~(1<<1);
	SPCR|=(1<<0);
#elif CLOCK_RATE==(1/64)
	SPCR|=(1<<1);
	SPCR&=~(1<<0);
#elif CLOCK_RATE==(1/128)
	SPCR|=(1<<1);
	SPCR|=(1<<0);
#else
#error "WRONG CLOCK RATE"
#endif


	return Local_enuErrorState;
}

ES_t SPI_enuTransfer(u8 Copy_u8Data,u8* Copy_pu8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	SPDR=Copy_u8Data;

	while(!((SPSR>>SPIF)&1));

	if(*Copy_pu8Data!=NULL)
	{
	    *Copy_pu8Data=SPDR;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

