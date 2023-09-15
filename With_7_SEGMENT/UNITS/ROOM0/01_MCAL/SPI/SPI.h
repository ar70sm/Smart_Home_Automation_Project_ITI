/*
 * SPI.h
 *
 *  Created on: Aug 31, 2023
 *      Author: ar70s
 */

#ifndef _MCAL_SPI_SPI_H_
#define _MCAL_SPI_SPI_H_

typedef enum{ SLAVE, MASTER }SPI_Mode;

void SPI_vidInit(SPI_Mode mode);
u8 SPI_u8SendReceive(u8 data);
void SPI_vidInterrupt(void (*ptr)(void));


#endif /* 01_MCAL_SPI_SPI_H_ */
