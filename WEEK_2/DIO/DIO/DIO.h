/*
 * DIO.h
 *
 * Created: 9/9/2022 1:18:13 AM
 *  Author: user
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "../../registers.h"
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'
#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1
#define DIO_ERROR 0
#define DIO_OK 1
uint8_t DIO_init(uint8_t portnumber,uint8_t pinnumber,uint8_t direction);//initialize directions
uint8_t DIO_write(uint8_t portnumber,uint8_t pinnumber,uint8_t value);
uint8_t DIO_toggle(uint8_t portnumber,uint8_t pinnumber);
uint8_t DIO_read(uint8_t portnumber,uint8_t pinnumber,uint8_t *value);
#endif /* DIO_H_ */