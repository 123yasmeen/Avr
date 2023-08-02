/*
 * ADC_priv.h
 *
 *  Created on: Jul 12, 2023
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_

//Registers
#define ADMUX              *((u8*)0x27)
#define ADCSRA             *((u8*)0x26)
#define ADCH               *((volatile u8*)0x25)
#define ADCL               *((volatile u8*)0x24)

#define SFIOR              *((u8*)0x50)

//Prescalers
#define PRES_2             2
#define PRES_4             4
#define PRES_8             8
#define PRES_16            16
#define PRES_32            32
#define PRES_64            64
#define PRES_128           128

//Voltage references
#define AVCC_REF           1
#define AREF_REF           2
#define INTERNAL_REF       3

//Adjusments
#define RIGHT_ADJ          1
#define LEFT_ADj           2


//Trigger sources
#define FREE_RUNNING_MODE            1
#define ANALOG_COMPARATOR            2
#define EXTI0                        3
#define TIMER0_COMPAREMATCH          4
#define TIMER0_OVF                   5

#endif /* MCAL_ADC_ADC_PRIV_H_ */
