/*
 * Timer0_priv.h
 *
 *  Created on: Jul 15, 2023
 *      Author: user
 */

#ifndef MCAL_TIMER0_TIMER0_PRIV_H_
#define MCAL_TIMER0_TIMER0_PRIV_H_

//Registers
#define TIMSK                        *((volatile u8*)0x59)
#define TCCR0                        *((volatile u8*)0x53)
#define TCNT0                        *((volatile u8*)0x52)
#define TIFR                         *((volatile u8*)0x58)

//Modes
#define OVF                           1
#define PWM_PHASECORRECT              2
#define CTC                           3
#define FAST_PWM                      4

//OC pin
#define CONNECTED                     1
#define DISCONNECTED                  0
#endif /* MCAL_TIMER0_TIMER0_PRIV_H_ */
