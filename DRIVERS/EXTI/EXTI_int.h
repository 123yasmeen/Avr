/*
 * EXTI_int.h
 *
 *  Created on: Jul 9, 2023
 *      Author: user
 */

#ifndef EXTI_INT_H_
#define EXTI_INT_H_

ES_t EXTI_enuInit(EXTI_t* Copy_pstrEXTIConfig);

ES_t EXTI_enuSelectSenseLevel(u8 Copy_u8EXTI_ID,u8 Copy_u8SenseLevel);//change sense level

ES_t EXTI_enuEnableINT(u8 Copy_u8EXTI_ID);

ES_t EXTI_enuDisableINT(u8 Copy_u8EXTI_ID);

ES_t EXTI_t_enuCallBack(void(*Copy_pfunApp)(void*),void* Copy_pvoidParameter,u8 Copy_u8EXTI_ID);

#endif /* EXTI_INT_H_ */
