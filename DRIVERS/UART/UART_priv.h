/*
 * UART_priv.h
 *
 *  Created on: Jul 15, 2023
 *      Author: user
 */

#ifndef UART_PRIV_H_
#define UART_PRIV_H_

//Registers
#define UCSRC                            *((volatile u8*)0x40)
#define UBRRH                            UCSRC
#define UDR                              *((volatile u8*)0x2C)
#define UCSRA                            *((volatile u8*)0x2B)
#define UCSRB                            *((volatile u8*)0x2A)
#define UBRRL                            *((volatile u8*)0x29)

//Flags
#define RXC/*recieve complete*/           7
#define UDRE/*data reg empty*/            5
//Speed Modes
#define NORMAL                            2
#define DOUBLE                            1

//Data length
#define FIVE_BIT                          5
#define SIX_BIT                           6
#define SEVEN_BIT                         7
#define EIGHT_BIT                         8
#define NINE_BIT                          9

//UART Modes
#define TRANSMITTER                       0
#define RECIEVER                          1
#define TRANSCIEVER                       2

//Parity
#define NO_PARITY                         0
#define EVEN_PARITY                       1
#define ODD_PARITY                        2

//Stop State
#define ONE_STOP_BIT                      1
#define TWO_STOP_BIT                      2

//Clock Modes
#define ASYCH                             0
#define SYCH                              1


//equation for baud rate
#define BAUDEQN(BAUD_RATE)                (u16)((F_CPU/SPEED_MODE*8*BAUD_RATE)-1)
#endif /* UART_PRIV_H_ */
