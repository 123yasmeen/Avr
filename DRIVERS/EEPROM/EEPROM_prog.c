/*
 * EEPROM_prog.c
 *
 *  Created on: Jul 31, 2023
 *      Author: user
 */

#include "stdTypes.h"
#include "errorStates.h"

#include "IIC_int.h"

#include "EEPROM_priv.h"
#include "EEPROM_config.h"

ES_t EEPROM_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState=IIC_enuInit();

	return Local_enuErrorState;
}

ES_t EEPROM_enuWriteData(u16 Copy_u16Address,u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

#if EEPROM_TYPE==EIGHT_KBIT

	//1010 0000->A0
#if EEPROM_A2_STATE==ENABLED

#if Copy_u16Address <= 1023
	u8 Local_u8Address=(0xA0|(EEPROM_A2_STATE<<3)|(((Copy_u16Address>>8)&3)<<1)>>1);//pure address without operation
	u8 Local_u8ByteAddress=(u8)Copy_u16Address;

#else
	Local_enuErrorState=ES_OUT_OF_RANGE;
#endif

#else
#error "A2 STATE MUST BE ENABLED"
#endif

#elif EEPROM_TYPE==FOUR_KBIT

#elif EEPROM_TYPE==TWO_KBIT

#else
#error "WRONG EEPROM TYPE"
#endif

	if(ES_OK==IIC_enuStartCondition())
	{
		if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,0))
		{
			if(ES_OK==IIC_enuWriteData(Local_u8ByteAddress))
			{
				if(ES_OK==IIC_enuWriteData(Copy_u8Data))
				{
					IIC_enuStopCondition();
					Local_enuErrorState=ES_OK;
				}
			}
		}
	}

	return Local_enuErrorState;
}

ES_t EEPROM_enuReadData(u16 Copy_u16Address,u8* Copy_pu8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

#if EEPROM_TYPE==EIGHT_KBIT

	//1010 0000->A0
#if EEPROM_A2_STATE==ENABLED

#if Copy_u16Address <= 1023
	u8 Local_u8Address=(0xA0|(EEPROM_A2_STATE<<3)|(((Copy_u16Address>>8)&3)<<1)>>1);//pure address without operation
	u8 Local_u8ByteAddress=(u8)Copy_u16Address;

#else
	Local_enuErrorState=ES_OUT_OF_RANGE;
#endif

#else
#error "A2 STATE MUST BE ENABLED"
#endif

#elif EEPROM_TYPE==FOUR_KBIT

#elif EEPROM_TYPE==TWO_KBIT

#else
#error "WRONG EEPROM TYPE"
#endif

	if(ES_OK==IIC_enuStartCondition())
	{
		if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,0))
		{
			if(ES_OK==IIC_enuWriteData(Local_u8ByteAddress))
			{
				if(ES_OK==IIC_enuRepeatedStartCondition())
				{
					if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,1))
					{
						if(ES_OK==IIC_enuReadData(&Copy_pu8Data))
						{
							IIC_enuStopCondition();
							Local_enuErrorState=ES_OK;
						}
					}
				}
			}
		}
	}


	return Local_enuErrorState;
}
