/*
 * TIMER0_prog.c
 *
 *  Created on: Aug 15, 2023
 *      Author: user
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"
#include "../../LIB/interrupt.h"

#include "TIMER0_priv.h"
#include "TIMER0_config.h"

static u32 Num_OVF=0;
static u8 PRELOAD;

static void (*TIMER0_pfunISR)(void*)=NULL;
static void * TIMER0_pvoidParameter=NULL;

ES_t TIMER0_enuInit(void)
{
	ES_t Local_enuErrorStates=ES_NOK;

	//checking timer mode and oc pin state
#if TIMER_MODE == OVF
	TCCR0 &= ~ ( TIMER0_MASK_BIT << WGM01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << WGM00 );

  #if OC_MODE == OVF_DISCONNECTED
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #else
  #error "Disable OC pin in OVF mode"
  #endif

#elif TIMER_MODE == PWM_PHASECORRECT
	TCCR0 &= ~ ( TIMER0_MASK_BIT << WGM01 );
	TCCR0 |= ( TIMER0_MASK_BIT << WGM00 );

  #if OC_MODE == PWM_PHCORRECT_CLEAR_UP
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |= ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #elif OC_MODE == PWM_PHCORRECT_SET_UP
	TCCR0 |= ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |= ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #else
  #error "WRONG OC STATE"
  #endif

#elif TIMER_MODE == CTC
	TCCR0 |= ( TIMER0_MASK_BIT << WGM01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << WGM00 );

  #if OC_MODE == CTC_TOGGLE
	TCCR0 |= ( TIMER0_MASK_BIT << COM00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #elif OC_MODE == CTC_CLEAR
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |=  ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #elif OC_MODE == CTC_SET
	TCCR0 |= ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |= ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #else
  #error "WRONG OC STATE"
  #endif

#elif TIMER_MODE == FAST_PWM
	TCCR0 |= ( TIMER0_MASK_BIT << WGM01 );
	TCCR0 |= ( TIMER0_MASK_BIT << WGM00 );

  #if OC_MODE == FAST_PWM_SET_TOP
	TCCR0 &= ~ ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |= ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #elif OC_MODE == FAST_PWM_CLEAR_TOP
	TCCR0 |= ( TIMER0_MASK_BIT << COM00 );
	TCCR0 |= ( TIMER0_MASK_BIT << COM01 );
	Local_enuErrorStates = ES_OK;
  #else
  #error "WRONG OC STATE"
  #endif

#else
#error "WRONG MODE"
#endif

//checking prescaler
#if TIMER_PRES == NO_CLK_SOURCE
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == NO_PRES
	TCCR0 |= ( TIMER0_MASK_BIT << CS00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == PRES_8
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS00 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == PRES_64
	TCCR0 |= ( TIMER0_MASK_BIT << CS00 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS01 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == PRES_256
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS01 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == PRES_1024
	TCCR0 |= ( TIMER0_MASK_BIT << CS00 );
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS01 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == EXT_CLK_FALLING_EDGE
	TCCR0 &= ~ ( TIMER0_MASK_BIT << CS00 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS01 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#elif TIMER_PRES == EXT_CLK_RISING_EDGE
	TCCR0 |= ( TIMER0_MASK_BIT << CS00 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS01 );
	TCCR0 |= ( TIMER0_MASK_BIT << CS02 );
	Local_enuErrorStates = ES_OK;
#else
#error "WRONG PRESCALER"
#endif

	return Local_enuErrorStates;
}

/*ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload)
{
	ES_t Local_enuErrorStates=ES_NOK;

	TCNT0 = Copy_u8Preload;

	return Local_enuErrorStates;
}*/

ES_t TIMER0_enuSetAsychDelay(u32 Copy_u32Time,void(*copy_pfunAPP)(void*),void* Copy_pvoidParameter)
{
	ES_t Local_enuErrorStates=ES_NOK;

#if TIMER_MODE == OVF

	f32 Local_f32NumOVF = ( Copy_u32Time / ( TIMER0_COUNTS * ( (f32) TIMER_PRES / TIMER_F_CPU ) ) );

	if( Local_f32NumOVF - (u32)Local_f32NumOVF != 0.0 )
	{
		u32 Local_u32INT_NUMOVF = (u32)Local_f32NumOVF + 1;

		Local_f32NumOVF = Local_f32NumOVF - (u32)Local_f32NumOVF;

		u8 Local_u8Preload = TIMER0_COUNTS - Local_f32NumOVF * TIMER0_COUNTS;

		Num_OVF = Local_u32INT_NUMOVF;

		PRELOAD = Local_u8Preload;

		TCNT0 = Local_u8Preload;
	}
	else
	{
		Local_f32NumOVF = (u32)Local_f32NumOVF;
	}

	if(copy_pfunAPP!=NULL)
		{
			TIMER0_pfunISR=copy_pfunAPP;
			TIMER0_pvoidParameter=Copy_pvoidParameter;
		}
	else
	{
		Local_enuErrorStates = ES_NULL_POINTER;
	}

	TIMSK |= (TIMER0_MASK_BIT << TOIE0 );
	Local_enuErrorStates = ES_OK;

#endif

	return Local_enuErrorStates;
}

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorStates=ES_NOK;

#if TIMER_MODE == FAST_PWM

  #if OC_MODE == FAST_PWM_SET_TOP
	OCR0 = (u8) ( (f32) TIMER0_FAST_COUNTS * ( (Copy_u8DutyCycle / 100.0) ) );
		Local_enuErrorStates = ES_OK;
  #elif OC_MODE == FAST_PWM_CLEAR_TOP
	OCR0 = (u8) (TIMER0_FAST_COUNTS - 1) - ( TIMER0_FAST_COUNTS * ( (Copy_u8DutyCycle / 100.0) ) ) ;
	Local_enuErrorStates = ES_OK;
  #endif

#elif TIMER_MODE == PWM_PHASECORRECT

  #if OC_MODE == PWM_PHCORRECT_CLEAR_UP
	OCR0 = (u8) ( TIMER0_PHASE_COUNTS * ( (Copy_u8DutyCycle /( 100.0 *2 ) ) ) );
	Local_enuErrorStates = ES_OK;
  #elif OC_MODE == PWM_PHCORRECT_SET_UP
	OCR0 = (u8) ( TIMER0_PHASE_COUNTS / 2) - ( TIMER0_PHASE_COUNTS * ( (Copy_u8DutyCycle / ( 100.0 * 2 ) ) );
	Local_enuErrorStates = ES_OK;
  #endif

#endif

	return Local_enuErrorStates;
}


ISR(VECT_TIMER0_OVF)
{
	if(TIMER0_pfunISR != NULL)
	{
		static u32 counts = 0;
		counts++;
		if(counts == Num_OVF)
		{
			TCNT0 = PRELOAD;
			TIMER0_pfunISR(TIMER0_pvoidParameter);
			counts=0;
		}
	}
}
