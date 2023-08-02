/*
 * LED_config.c
 *
 *  Created on: Feb 13, 2023
 *      Author: user
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"
#include "LED_config.h"
#include "LED_priv.h"

LED_t LED_AstrLedConfig [LED_NUM]={
		{DIO_u8PORTA,DIO_u8PIN0,LED_SINK,LED_OFF},
		{DIO_u8PORTA,DIO_u8PIN1,LED_SINK,LED_OFF},
		{DIO_u8PORTA,DIO_u8PIN2,LED_SINK,LED_OFF},
};
