/*
 * EEPROM_int.h
 *
 *  Created on: Jul 31, 2023
 *      Author: user
 */

#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

ES_t EEPROM_enuInit(void);

ES_t EEPROM_enuWriteData(u16 Copy_u16Address,u8 Copy_u8Data);

ES_t EEPROM_enuReadData(u16 Copy_u16Address,u8* Copy_pu8Data);


#endif /* EEPROM_INT_H_ */
