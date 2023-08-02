/*
 * SPI_config.h
 *
 *  Created on: Jul 17, 2023
 *      Author: user
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define MOSI_PORT                DIO_u8PORTB
#define MISO_PORT                DIO_u8PORTB
#define CLK_PORT                 DIO_u8PORTB
#define SS_PORT                  DIO_u8PORTB


#define MOSI_PIN                 DIO_u8PIN5
#define MISO_PIN                 DIO_u8PIN6
#define CLK_PIN                  DIO_u8PIN7
#define SS_PIN                   DIO_u8PIN4

#define DATA_ORDER                    LSB

#define CLOCK_POLARITY                HIGH

#define CLOCK_PHASE                   SETUP_LEADING

#define CLOCK_RATE                    (1/64)

#define DOUBLE_SPI_SPEED              ENABLED

#endif /* SPI_CONFIG_H_ */
