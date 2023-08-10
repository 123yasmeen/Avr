/*
 * ADC_prog.c


 *
 *  Created on: Jul 12, 2023
 *      Author: user
 */
#include "../../stdTypes.h"
#include "../../errorStates.h"

#include "ADC_config.h"
#include "ADC_priv.h"

#include "../../interrupt.h"

static void (*ADC_pfunISR)(void*)=NULL;
static void * ADC_pvoidParameter=NULL;

ES_t ADC_enuInit(void)
{
	ES_t Local_enuErrorStates=ES_NOK;
	ADMUX=0x00;
	ADCSRA=0x00;

#if ADC_REF_VOLT==AVCC_REF
	ADMUX|=(1<<6);
#elif ADC_REF_VOLT==AREF_REF

#elif ADC_REF_VOLT==INTERNAL_REF
	ADMUX|=(1<<6);
	ADMUX|=(1<<7);
#else
#error "WRONG REFERENCE VOLTAGE"
#endif

#if ADC_ADJUSTMENT==LEFT_ADj
	ADMUX|=(1<<5);
#elif ADC_ADJUSTMENT==RIGHT_ADJ
	ADMUX&=~(1<<5);
#else
#error "WRONG ADJUSTMENT"
#endif

#if ADC_PRES==PRES_2
	ADCSRA|=(1<<0);
#elif ADC_PRES==PRES_4
	ADCSRA|=(1<<1);
#elif ADC_PRES==PRES_8
	ADCSRA|=(1<<0);
	ADCSRA|=(1<<1);
#elif ADC_PRES==PRES_16
	ADCSRA|=(1<<2);
#elif ADC_PRES==PRES_32
	ADCSRA|=(1<<0);
	ADCSRA|=(1<<2);
#elif ADC_PRES==PRES_64
	ADCSRA|=(1<<1);
	ADCSRA|=(1<<2);
#elif ADC_PRES==PRES_128
	ADCSRA|=(1<<0);
	ADCSRA|=(1<<1);
	ADCSRA|=(1<<2);
#else
#error "WRONG PRESCALER "
#endif


	return Local_enuErrorStates;
}

ES_t ADC_enuStartConversion(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA|=(1<<6);

	return Local_enuErrorStates;
}

ES_t ADC_enuPollingSystem(void)//waiting for flag to be set
{
	ES_t Local_enuErrorStates=ES_NOK;
	//wait for ADC interrupt flag
	while(!((ADCSRA>>4)&1));
	ADCSRA|=(1<<4);

	return Local_enuErrorStates;
}

ES_t ADC_enuReadHighValue(u8* Copy_pu8Value)
{
	//Reading bits from 2 to 9
	ES_t Local_enuErrorStates=ES_NOK;

#if ADC_ADJUSTMENT==LEFT_ADj
    * Copy_pu8Value=ADCH;
#elif ADC_ADJUSTMENT==RIGHT_ADJ
    //Right shifting ADCL
    *Copy_pu8Value=(ADCL>>2);
    //or with ADCH left shifted
    *Copy_pu8Value|=(ADCH<<6);
#else
#error "WRONG ADJUSTMENT"
#endif

	return Local_enuErrorStates;
}

ES_t ADC_enuRead(u16* Copy_pu16Value)
{
	ES_t Local_enuErrorStates=ES_NOK;

#if ADC_ADJUSTMENT==LEFT_ADj
    * Copy_pu16Value=(ADCL>>6);
    * Copy_pu16Value|=(ADCH<<2);
#elif ADC_ADJUSTMENT==RIGHT_ADJ
    *Copy_pu16Value=ADCL;
    //or with ADCH left shifted
    *Copy_pu16Value|=((u16)ADCH<<8);
#else
#error "WRONG ADJUSTMENT"
#endif
	return Local_enuErrorStates;
}

ES_t ADC_enuSelectChannel(u8 Copy_u8Channel_ID)
{
	ES_t Local_enuErrorStates=ES_NOK;

	if(Copy_u8Channel_ID<=7)
	{
	    //masking bits for 0 to 4
	    ADMUX &=~ 0x1F;
	    ADMUX|= Copy_u8Channel_ID;
	    Local_enuErrorStates=ES_OK;
	}
	else
	{
		Local_enuErrorStates=ES_OUT_OF_RANGE;
	}
	return Local_enuErrorStates;
}

ES_t ADC_enuEnable(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA|=(1<<7);

	return Local_enuErrorStates;
}

ES_t ADC_enuDisable(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA &=~(1<<7);

	return Local_enuErrorStates;
}

ES_t ADC_enuEnableInterruptMode(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA|=(1<<3);

	return Local_enuErrorStates;
}

ES_t ADC_enuDisableInterruptMode(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA&=~(1<<3);

	return Local_enuErrorStates;
}

ES_t ADC_enuCallBack(void(*Copy_pfunApp)(void*),void* Copy_pvoidParameter)//Call back function for interrupt
{
	ES_t Local_enuErrorStates=ES_NOK;


	if(Copy_pfunApp!=NULL)
	{
		ADC_pfunISR=Copy_pfunApp;
		ADC_pvoidParameter=Copy_pvoidParameter;
	}
	else
	{
	  Local_enuErrorStates=ES_NULL_POINTER;
	}

	return Local_enuErrorStates;
}

ES_t ADC_enuEnableTriggerMode(u8 Copy_u8Trigger)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA &=~(1<<5);
	switch(Copy_u8Trigger)
	{
	case FREE_RUNNING_MODE:
		SFIOR&=~(1<<5);
		SFIOR&=~(1<<6);
		SFIOR&=~(1<<7);
		break;
	case ANALOG_COMPARATOR:
		SFIOR|=(1<<5);
		SFIOR&=~(1<<6);
		SFIOR&=~(1<<7);
		break;
	case EXTI0:
		SFIOR&=~(1<<5);
		SFIOR|=(1<<6);
		SFIOR&=~(1<<7);
		break;
	case TIMER0_COMPAREMATCH:
		SFIOR|=(1<<5);
		SFIOR|=(1<<6);
		SFIOR&=~(1<<7);
		break;
	}
	ADCSRA|=(1<<5);

	return Local_enuErrorStates;
}

ES_t ADC_enuDisableTriggerMode(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	ADCSRA &=~(1<<5);

	return Local_enuErrorStates;
}

ISR(VECT_ADC)
{
	if(ADC_pfunISR!=NULL)
	{
		ADC_pfunISR(ADC_pvoidParameter);
	}

}
