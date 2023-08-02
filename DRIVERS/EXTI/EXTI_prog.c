/*
 * EXTI_prog.c
 *
 *  Created on: Jul 9, 2023
 *      Author: user
 */
#include "../../stdTypes.h"
#include "../../errorStates.h"

#include "EXTI_priv.h"
#include "EXTI_config.h"

#include "../../Interrupt.h"

//Global pointer to function
static volatile void (* EXTI_pFunINT[3])(void*)={NULL,NULL,NULL};


static volatile void * EXTI_ApvoidParameter[3]={NULL,NULL,NULL};

ES_t EXTI_enuInit(EXTI_t* Copy_pstrEXTIConfig)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pstrEXTIConfig !=NULL)
	{
	  u8 Local_u8Iter=0;
	  for(Local_u8Iter=0;Local_u8Iter<3;Local_u8Iter++)
	  {
		if(Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8State == ENABLED)
		{
			switch(Local_u8Iter)
			{
			case 0:
				//External interrupt request 0 enable
				GICR |= (1<<6);
				MCUCR&=~(3<<0);
				switch(Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
				{
				case RISING_EDGE:
					MCUCR|=(1<<0);
					MCUCR|=(1<<1);
					break;
				case FALLING_EDGE:
					MCUCR|=(1<<1);
					break;
				case LOGICAL_CHANGE:
					MCUCR|=(1<<0);
					break;
				case LOW_LEVEL:
					break;
				default:
					Local_enuErrorState = ES_OUT_OF_RANGE;

				}
				break;
			case 1:
				//External interrupt request 1 enable
				GICR |= (1<<7);
				MCUCR&=~(3<<2);
				switch(Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
				{
				case RISING_EDGE:
					MCUCR|=(1<<2);
					MCUCR|=(1<<3);
					break;
				case FALLING_EDGE:
					MCUCR|=(1<<3);
					break;
				case LOGICAL_CHANGE:
					MCUCR|=(1<<2);
					break;
				case LOW_LEVEL:
					break;
				default:
					Local_enuErrorState = ES_OUT_OF_RANGE;

				}
				break;
			case 2:
				//External interrupt request 2 enable
				GICR |= (1<<5);
				MCUCSR&=~(1<<6);
				switch(Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8SenseLevel)
				{
				case RISING_EDGE:
					MCUCSR|=(1<<6);
					break;
				case FALLING_EDGE:
					break;
				default:
					Local_enuErrorState = ES_OUT_OF_RANGE;

				}
				break;

			}
		}
	  }

	}

	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuSelectSenseLevel(u8 Copy_u8EXTI_ID,u8 Copy_u8SenseLevel)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8EXTI_ID <3)
	{

		if(Copy_u8EXTI_ID==0)
		{
			//Masking
			MCUCR&=~(3<<0);

			switch(Copy_u8SenseLevel)
			{
			case RISING_EDGE:
				MCUCR|=(1<<0);
				MCUCR|=(1<<1);
				break;
			case FALLING_EDGE:
				MCUCR|=(1<<1);
				break;
			case LOGICAL_CHANGE:
				MCUCR|=(1<<0);
				break;
			case LOW_LEVEL:
				break;
			default:
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else if(Copy_u8EXTI_ID==1)
		{
			//Masking
			MCUCR&=~(3<<2);

        	switch(Copy_u8SenseLevel)
        	{
        	case RISING_EDGE:
        		MCUCR|=(1<<2);
        		MCUCR|=(1<<3);
        		break;
        	case FALLING_EDGE:
        		MCUCR|=(1<<3);
        		break;
        	case LOGICAL_CHANGE:
        		MCUCR|=(1<<2);
        		break;
        	case LOW_LEVEL:
        		break;
        	default:
        		Local_enuErrorState = ES_OUT_OF_RANGE;
        	}


		}
		else if(Copy_u8EXTI_ID==2)
		{
			MCUCSR&=~(1<<6);

			switch(Copy_u8SenseLevel)
			{
			case RISING_EDGE:
     			MCUCSR|=(1<<6);
     			break;
     		case FALLING_EDGE:
     			break;
     		default:
     			Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8EXTI_ID<3)
	{
     if(Copy_u8EXTI_ID==0)
        {
        	GICR|=(1<<6);
        }
	else if(Copy_u8EXTI_ID==1)
		{
			GICR|=(1<<7);
		}
	else if(Copy_u8EXTI_ID==2)
		{
			GICR|=(1<<5);
		}
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8EXTI_ID<3)
	{
     if(Copy_u8EXTI_ID==0)
        {
        	GICR&=~(1<<6);
        }
	else if(Copy_u8EXTI_ID==1)
		{
			GICR&=~(1<<7);
		}
	else if(Copy_u8EXTI_ID==2)
		{
			GICR&=~(1<<5);
		}
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t EXTI_t_enuCallBack(volatile void(*Copy_pfunApp)(void*),volatile void* Copy_pvoidParameter,u8 Copy_u8EXTI_ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pfunApp !=NULL)
	{

		if(Copy_u8EXTI_ID<3)
		{

			EXTI_pFunINT[Copy_u8EXTI_ID]=Copy_pfunApp;
			EXTI_ApvoidParameter[Copy_u8EXTI_ID]=Copy_pvoidParameter;
		}
		else
		{
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ISR(VECT_INT0)
{

	if (EXTI_pFunINT[0]!=NULL)
	{
		EXTI_pFunINT[0](EXTI_ApvoidParameter[0]);
	}
}

ISR(VECT_INT1)
{

	if (EXTI_pFunINT[1]!=NULL)
	{
		EXTI_pFunINT[1](EXTI_ApvoidParameter[1]);
	}
}
ISR(VECT_INT2)
{

	if (EXTI_pFunINT[2]!=NULL)
	{
		EXTI_pFunINT[2](EXTI_ApvoidParameter[2]);
	}
}
