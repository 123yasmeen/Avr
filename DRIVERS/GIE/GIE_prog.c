/*
 * GIE_prog.c

 *
 *  Created on: Jul 12, 2023
 *      Author: user
 */
#include "../../stdTypes.h"
#include "../../errorStates.h"

#include "GIE_priv.h"


ES_t GIE_enuEnable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG|=(1<<7);

	return Local_enuErrorState;
}

ES_t GIE_enuDisable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG&=~(1<<7);

	return Local_enuErrorState;
}

