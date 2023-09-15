/*
 * EEPROM.h
 *
 *  Created on: Sep 9, 2023
 *      Author: ar70s
 */

#ifndef _HAL_EEPROM_EEPROM_H_
#define _HAL_EEPROM_EEPROM_H_

void EEPROM_vidWriteChar(u8 blockAddress,u8 dataAddress,u8 data);
void EEPROM_vidWriteString(u8 blockAddress,u8 dataAddress,u8 data[]);
u8 EEPROM_u8readChar(u8 blockAddress,u8 dataAddress);

#endif /* 02_HAL_EEPROM_EEPROM_H_ */
