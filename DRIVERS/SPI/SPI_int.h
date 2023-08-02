/*
 * SPI_int.h
 *
 *  Created on: Jul 17, 2023
 *      Author: user
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_

ES_t SPI_enuInitMasterMode(void);

ES_t SPI_enuInitSlaveMode(void);

ES_t SPI_enuTransfer(u8 Copy_u8Data,u8* Copy_pu8Data);


#endif /* SPI_INT_H_ */
