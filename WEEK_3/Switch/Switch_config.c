/*
 * Switch_config.c
 *
 *  Created on: Feb 10, 2023
 *      Author: user
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "Switch_priv.h"
#include "Switch_config.h"
#include "DIO_int.h"
SW_t Switch_AstrSwitchState[SW_NUM]={
		{DIO_u8PORTA,DIO_u8PIN4,DIO_u8FLOAT},
		{DIO_u8PORTA,DIO_u8PIN4,DIO_u8FLOAT},
		{DIO_u8PORTA,DIO_u8PIN4,DIO_u8FLOAT}
};

