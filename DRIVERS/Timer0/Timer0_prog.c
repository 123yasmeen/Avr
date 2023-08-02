/*
 * Timer0_prog.c
 *
 *  Created on: Jul 15, 2023
 *      Author: user
 */
#include "../../stdTypes.h"
#include "../../errorStates.h"

#include "Timer0_priv.h"
#include "Timer0_config.h"

#include"../../Interrupt.h"

static u32 Num_OVF=0;
static u8 PRELOAD;

static void (*TIMER0_pfunISR)(void*)=NULL;
static void * TIMER0_pvoidParameter=NULL;

ES_t TIMER0_enuInit(void)
{

	ES_t Local_enuErrorState=ES_NOK;

#if TIMER_MODE==OVF
	TCCR0&=~(1<<3);
	TCCR0&=~(1<<6);
#elif TIMER_MODE==PWM_PHASECORRECT
	TCCR0&=~(1<<3);
	TCCR0|=(1<<6);
#elif TIMER_MODE==CTC
	TCCR0|=(1<<3);
	TCCR0&=~(1<<6);
#elif TIMER_MODE==FAST_PWM
	TCCR0|=(1<<3);
	TCCR0|=(1<<6);
#else
#error "WRONG TIMER MODE"
#endif

#if OC_MODE==DISCONNECTED
	TCCR0&=~(1<<4);
	TCCR0&=~(1<<5);
#endif

#if TIMER_PRES==64
	TCCR0|=(1<<0);
	TCCR0|=(1<<1);
	TCCR0&=~(1<<2);
#elif TIMER_PRES==256
	TCCR0&=~(1<<0);
	TCCR0&=~(1<<1);
	TCCR0|=(1<<2);
#elif TIMER_PRES==1024
	TCCR0|=(1<<0);
	TCCR0&=~(1<<1);
	TCCR0|=(1<<2);
#else
#error "Wrong Prescalar"
#endif

	return Local_enuErrorState;

}

ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload)
{

	ES_t Local_enuErrorState=ES_NOK;

	TCNT0=Copy_u8Preload;

	return Local_enuErrorState;

}

ES_t TIMER0_enuSetAsychDelay(u32 Copy_u32Time,void(*copy_pfunAPP)(void*),void* Copy_pvoidParameter)//depends on ISR
{

	ES_t Local_enuErrorState=ES_NOK;

	f32 OVFtime=256*((f32)TIMER_PRES/TIMER_F_CPU);
	f32 NumOVF=(Copy_u32Time/OVFtime);

	if((NumOVF-(u32)NumOVF)!=0.0)//there is a fraction
	{
		u32 NumOVFint=(u32)NumOVF+1;
		NumOVF=NumOVF-(u32)NumOVF;
		u8 preload=256-(NumOVF*256);
		Num_OVF=NumOVFint;
		PRELOAD=preload;
		TCNT0=preload;
	}
	else
	{
		Num_OVF=(u32)NumOVF;
	}

	if(copy_pfunAPP!=NULL)
	{
		TIMER0_pfunISR=copy_pfunAPP;
		TIMER0_pvoidParameter=Copy_pvoidParameter;
	}

	TIMSK|=(1<<0);

	return Local_enuErrorState;

}

ES_t TIMER0_enuSetSychDelay(u32 Copy_u32Time)//polling
{

	ES_t Local_enuErrorState=ES_NOK;

	TIMSK &=~(1<<0);

	f32 OVFtime=256*((f32)TIMER_PRES/TIMER_F_CPU);
	f32 NumOVF=(Copy_u32Time/OVFtime);

	if((NumOVF-(u32)NumOVF)!=0.0)//there is a fraction
	{
		u32 NumOVFint=(u32)NumOVF+1;
		NumOVF=NumOVF-(u32)NumOVF;
		u8 preload=256-(NumOVF*256);
		TCNT0=preload;
		while(NumOVFint>0)
		{
			while(((TIFR>>0)&1)==0);
			TIFR|=(1<<0);//clear the flag
			NumOVFint--;
		}
	}
	else
	{
		u32 NumOVFint=(u32)NumOVF;
		while(NumOVFint>0)
		{
			while(((TIFR>>0)&1)==0);
			TIFR|=(1<<0);//clear the flag
			NumOVFint--;
		}
	}


	return Local_enuErrorState;
}

ISR(VECT_TIMER0_OVF)
{
	if(TIMER0_pfunISR!=NULL)
	{
		static u32 counts=0;
		counts--;
		if(counts==Num_OVF)
		{
			TCNT0=PRELOAD;
			TIMER0_pfunISR(TIMER0_pvoidParameter);
			counts=0;
		}
	}
}
