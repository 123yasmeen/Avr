/*
 * IIC_prog.c
 *
 *  Created on: Jul 26, 2023
 *      Author: user
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "IIC_priv.h"
#include "IIC_config.h"

ES_t IIC_enuInit(void)
{

	ES_t Local_enuErrorState=ES_NOK;

#if IIC_MODE==MASTER
	TWBR=(u8)BITRATE(IIC_CLOCK_SPEED);
#if IIC_PRES==PRES_1
	TWSR&=~(1<<1);
	TWSR&=~(1<<0);
#elif IIC_PRES==PRES_4
	TWSR&=~(1<<1);
	TWSR|=(1<<0);
#elif IIC_PRES==PRES_16
	TWSR|=(1<<1);
	TWSR&=~(1<<0);
#elif IIC_PRES==PRES_64
	TWSR|=(1<<1);
	TWSR|=(1<<0);
#else
#error "WRONG PRESACLAR"
#endif

	TWAR=0;
	TWAR=(IIC_NODE_ADDRESS<<1)|IIC_GENERAL_CALL;

	TWCR|=(1<<7);
	TWCR|=(1<<2);

#elif IIC_MODE==SLAVE
	TWAR=0;
	TWAR=(IIC_NODE_ADDRESS<<1)|IIC_GENERAL_CALL;

	TWCR|=(1<<7);
	TWCR|=(1<<2);
#else
#error "WRONG IIC MODE"
#endif

	return Local_enuErrorState;
}

ES_t IIC_enuStartCondition(void)
{

	ES_t Local_enuErrorState=ES_NOK;

	//set TWI start condition bit
	TWCR|=(1<<5);
	//clear flag
	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x08)
		Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t IIC_enuRepeatedStartCondition(void)
{

	ES_t Local_enuErrorState=ES_NOK;

	TWCR|=(1<<5);

	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x10)
		 Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t IIC_enuStopCondition(void)
{

	ES_t Local_enuErrorState=ES_NOK;

	TWCR|=(1<<7);

	TWCR|=(1<<4);

	return Local_enuErrorState;
}

ES_t IIC_enuWriteSlaveAddress(u8 Copy_u8SlaveAddress,u8 Copy_u8Operation)
{

	ES_t Local_enuErrorState=ES_NOK;

	TWDR=((Copy_u8SlaveAddress<<1)|Copy_u8Operation);

	TWCR&=~(1<<5);
	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x18 && Copy_u8Operation==0)
		Local_enuErrorState=ES_OK;
	else if((TWSR & 0xF8)==0x40 && Copy_u8Operation==1)
		Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t IIC_enuWriteData(u8 Copy_u8Data)
{

	ES_t Local_enuErrorState=ES_NOK;

	TWDR=Copy_u8Data;

	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x28)
		Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t IIC_enuCheckAddress(void)
{

	ES_t Local_enuErrorState=ES_NOK;

	//enable ack bit
	TWCR|=(1<<6);

	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x60)
		Local_enuErrorState=ES_OK;
	else if((TWSR & 0xF8)==0xA8)
		Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t IIC_enuReadData(u8* Copy_pu8Data)
{

	ES_t Local_enuErrorState=ES_NOK;

	TWCR|=(1<<7);

	while(!((TWCR>>7)&1));

	if((TWSR & 0xF8)==0x50)
	{
		*Copy_pu8Data=TWDR;
		Local_enuErrorState=ES_OK;
	}
	else if((TWSR & 0xF8)==0x80)
	{
		*Copy_pu8Data=TWDR;
		Local_enuErrorState=ES_OK;
	}

	return Local_enuErrorState;
}

