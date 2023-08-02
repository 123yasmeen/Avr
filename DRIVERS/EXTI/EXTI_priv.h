/*
 * EXTI_priv.h
 *
 *  Created on: Jul 9, 2023
 *      Author: user
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_

//External interrupt registers

#define MCUCR      *((volatile u8*)0x55)
#define MCUCSR     *((volatile u8*)0x54)
#define GICR       *((volatile u8*)0x5B)
#define GIFR       *((volatile u8*)0x5A)

//External interrupt configuration

#define INT0            0
#define INT1            1
#define INT2            2

//State of interrupt

#define ENABLED         1
#define DISABLED        0

//Sense Modes

#define RISING_EDGE     1
#define FALLING_EDGE    2
#define LOW_LEVEL       3
#define LOGICAL_CHANGE  4
#endif /* EXTI_PRIV_H_ */
