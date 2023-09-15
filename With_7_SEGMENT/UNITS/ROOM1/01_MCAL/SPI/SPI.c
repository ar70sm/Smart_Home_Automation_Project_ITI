/*
 * SPI.c
 *
 *  Created on: Aug 31, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/DIO/DIO.h"
#include "SPI.h"
#include "private.h"

void (*SPI_ptr)(void);

void SPI_vidInit(SPI_Mode mode)
{
	DIO_vidSetPinDirection(PORT_B,PIN_4,mode);
	DIO_vidSetPinDirection(PORT_B,PIN_5,mode);
	DIO_vidSetPinDirection(PORT_B,PIN_6,(!mode));
	DIO_vidSetPinDirection(PORT_B,PIN_7,mode);
	ADJ_MSTR(mode);
	ADJ_SPE(HIGH);
}


u8 SPI_u8SendReceive(u8 data)
{
	SPDR=data;
	while(!GET_SPIF);
	return SPDR;
}


void SPI_vidInterrupt(void (*ptr)(void)){
	ADJ_SPIE(HIGH);
	SPI_ptr=ptr;
}


void __vector_12 (void) __attribute__ ((signal,used, externally_visible)) ;\

void __vector_12  (void){
	SPI_ptr();
}

