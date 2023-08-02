/*
 * UART_int.h
 *
 *  Created on: Jul 15, 2023
 *      Author: user
 */

#ifndef UART_INT_H_
#define UART_INT_H_

ES_t UART_enuInit(void);

ES_t UART_enuSendChar(u8 Copy_u8Data);

ES_t UART_enuRecieveChar(u8 *Copy_u8Data);

ES_t UART_enuSendString(const char* Copy_sData);

ES_t UART_enuRecieveString(char* Copy_sData);

#endif /* UART_INT_H_ */
