/*
 * main.c
 *
 *  Created on: Feb 13, 2023
 *      Author: user
 */
#include "stdTypes.h"
#include "errorStates.h"
#include "DIO_int.h"
#include "LED_config.h"
#include "LED_int.h"


extern LED_t LED_AstrLedConfig [LED_NUM];
int main(void)
{
	DIO_enuInit();
	LED_enuInit(LED_AstrLedConfig);
	return 0;
}

