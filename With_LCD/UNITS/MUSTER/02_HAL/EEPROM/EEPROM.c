/*
 * EEPROM.c
 *
 *  Created on: Sep 9, 2023
 *      Author: ar70s
 */

#include "../../00_UB/STD_TYPES.h"
#include "../../01_MCAL/TWI/TWI.h"
#include "EEPROM.h"


void EEPROM_vidWriteChar(u8 blockAddress,u8 dataAddress,u8 data){
	 TWI_u8SendStart();
	 TWI_u8SendAddress(0b1010000+blockAddress,Write);
	 TWI_u8SendData(dataAddress);
	 TWI_u8SendData(data);
	 TWI_u8SendStop();
}
void EEPROM_vidWriteString(u8 blockAddress,u8 dataAddress,u8 data[]){
	u16 i=0;
	 TWI_u8SendStart();
	 TWI_u8SendAddress(0b1010000+blockAddress,Write);
	 TWI_u8SendData(dataAddress);
	 while (data[i]){
		 TWI_u8SendData(data[i]);
		 i++;
	 }
	 TWI_u8SendStop();
}
u8 EEPROM_u8readChar(u8 blockAddress,u8 dataAddress){
	u8 st;
	 TWI_u8SendStart();
	 TWI_u8SendAddress(0b1010000+blockAddress,Write);
	 TWI_u8SendData(dataAddress);
	 TWI_u8SendStart();
	 TWI_u8SendAddress(0b1010000+blockAddress,Read);
	 TWI_u8Get(&st);
	 TWI_u8SendStop();
	 return st;
}
