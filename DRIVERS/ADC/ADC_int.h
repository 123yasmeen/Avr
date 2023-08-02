/*
 * ADC_int.h
 *
 *  Created on: Jul 12, 2023
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

ES_t ADC_enuInit(void);

ES_t ADC_enuStartConversion(void);

ES_t ADC_enuPollingSystem(void); //waiting for flag to be set

ES_t ADC_enuReadHighValue(u8* Copy_pu8Value);

ES_t ADC_enuRead(u16* Copy_pu16Value);

ES_t ADC_enuSelectChannel(u8 Copy_u8Channel_ID);

ES_t ADC_enuEnable(void);

ES_t ADC_enuDisable(void);

ES_t ADC_enuEnableInterruptMode(void);

ES_t ADC_enuDisableInterruptMode(void);

ES_t ADC_enuCallBack(void(*Copy_pfunApp)(void*),void* Copy_pvoidParameter);//Call back function for interrupt

ES_t ADC_enuEnableTriggerMode(u8 Copy_u8Trigger);

ES_t ADC_enuDisableTriggerMode(void);

#endif /* MCAL_ADC_ADC_INT_H_ */
