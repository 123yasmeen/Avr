/*
 * EXTI_config.c

 *
 *  Created on: Jul 9, 2023
 *      Author: user
 */
#include "../../stdTypes.h"
#include "../../errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

EXTI_t EXTI_t_ArrstrEXTIConfig[3]=
{
		{ENABLED,FALLING_EDGE},
		{DISABLED},
		{DISABLED}
};

