/*
 * TIMER0_priv.h
 *
 *  Created on: Aug 15, 2023
 *      Author: user
 */

#ifndef MCAL_TIMER0_TIMER0_PRIV_H_
#define MCAL_TIMER0_TIMER0_PRIV_H_

//Registers
#define TIMSK                        *((volatile u8*)0x59)

#define OCIE0                              1
#define TOIE0                              0

/*********************************************************************/

#define TCCR0                        *((volatile u8*)0x53)

#define FOC0                               7
#define WGM00                              6
#define COM01                              5
#define COM00                              4
#define WGM01                              3
#define CS02                               2
#define CS01                               1
#define CS00                               0

/*******************************************************************/

#define TCNT0                        *((volatile u8*)0x52)

/******************************************************************/

#define TIFR                         *((volatile u8*)0x58)

#define OCF0                               1
#define TOV0                               0

#define OCR0					     *((volatile u8*) 0x5c)


//Modes
#define OVF                                1
#define PWM_PHASECORRECT                   2
#define CTC                                3
#define FAST_PWM                           4

//OC pin state
#define OVF_CONNECTED                      1
#define OVF_DISCONNECTED                   0

#define CTC_SET                            1
#define CTC_CLEAR                          0
#define CTC_TOGGLE                         2

#define FAST_PWM_SET_TOP                   1
#define FAST_PWM_CLEAR_TOP                 0

#define PWM_PHCORRECT_SET_UP               1
#define PWM_PHCORRECT_CLEAR_UP             0

//PRES
#define PRES_1024                          1024
#define PRES_256                           256
#define PRES_64                            64
#define PRES_8                             8
#define NO_PRES                            1
#define NO_CLK_SOURCE                      6
#define EXT_CLK_FALLING_EDGE               7
#define EXT_CLK_RISING_EDGE                8

#define TIMER0_MASK_BIT                    1

#define TIMER0_COUNTS                      256

#define TIMER0_FAST_COUNTS                 256
#define TIMER0_PHASE_COUNTS                510


#endif /* MCAL_TIMER0_TIMER0_PRIV_H_ */
