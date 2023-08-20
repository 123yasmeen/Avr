/*
 * TIMER0_int.h
 *
 *  Created on: Aug 15, 2023
 *      Author: user
 */

#ifndef MCAL_TIMER0_TIMER0_INT_H_
#define MCAL_TIMER0_TIMER0_INT_H_

ES_t TIMER0_enuInit(void);

ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload);

ES_t TIMER0_enuSetAsychDelay(u32 Copy_u32Time,void(*copy_pfunAPP)(void*),void* Copy_pvoidParameter);

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle);

ES_t TIMER0_enuCallBackCTC(void(*copy_pfunAPP)(void*),void* Copy_pvoidParameter);


#endif /* MCAL_TIMER0_TIMER0_INT_H_ */
