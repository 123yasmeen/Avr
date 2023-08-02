/*
 * SPI_priv.h
 *
 *  Created on: Jul 17, 2023
 *      Author: user
 */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

//registers
#define SPDR                                    *((volatile u8*)0x2F)
#define SPSR                                    *((volatile u8*)0x2E)
#define SPCR                                    *((volatile u8*)0x2D)

//Data Order
#define LSB                                      1
#define MSB                                      2

//Clock polarity
#define HIGH                                     1
#define LOW                                      2

//Clock phase
#define SAMPLE_LEADING                           1
#define SETUP_LEADING                            2

//Double speed
#define ENABLED                                  1
#define DISABLED                                 2

//Flag
#define SPIF                                     7

#endif /* SPI_PRIV_H_ */
