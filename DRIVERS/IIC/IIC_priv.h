/*
 * IIC_priv.h
 *
 *  Created on: Jul 26, 2023
 *      Author: user
 */

#ifndef IIC_PRIV_H_
#define IIC_PRIV_H_

//registers
#define TWDR                                  *((volatile u8*)0x23)
#define TWAR                                  *((volatile u8*)0x22)
#define TWSR                                  *((volatile u8*)0x21)
#define TWBR                                  *((volatile u8*)0x20)
#define TWCR                                  *((volatile u8*)0x56)

//Bit Rate equation
#define BITRATE(IIC_SPEED)                    ((F_CPU-16ul*IIC_SPEED)/(2ul*IIC_SPEED*IIC_PRES))

//IIC mode
#define MASTER                                 1
#define SLAVE                                  2

//IIC presaclar
#define PRES_1                                 1ul
#define PRES_4                                 4ul
#define PRES_16                                16ul
#define PRES_64                                64ul

//IIC general call
#define ENABLED                                 1
#define DISABLED                                0


#endif /* IIC_PRIV_H_ */
