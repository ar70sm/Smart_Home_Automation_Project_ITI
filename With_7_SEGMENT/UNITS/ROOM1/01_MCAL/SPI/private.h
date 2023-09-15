/*
 * private.h
 *
 *  Created on: Sep 5, 2023
 *      Author: ar70s
 */

#ifndef _MCAL_SPI_PRIVATE_H_
#define _MCAL_SPI_PRIVATE_H_

/* Registers definitions */
#define SPCR       (*(volatile u8*)0x2D) // SPI Control Register
#define SPSR       (*(volatile u8*)0x2E) // SPI Status Register
#define SPDR       (*(volatile u8*)0x2F) // SPI I/O Data Register

/* SPCR Register */
enum {SPR0,SPR1,CPHA,CPOL,MSTR,DORD,SPE,SPIE};
#define ADJ_SPIE(VALUE)  ADJ_BIT(SPCR,SPIE,VALUE)
#define ADJ_SPE(VALUE)   ADJ_BIT(SPCR,SPE,VALUE)
#define ADJ_DORD(VALUE)  ADJ_BIT(SPCR,DORD,VALUE)
#define ADJ_MSTR(VALUE)  ADJ_BIT(SPCR,MSTR,VALUE)
#define ADJ_CPOL(VALUE)  ADJ_BIT(SPCR,CPOL,VALUE)
#define ADJ_CPHA(VALUE)  ADJ_BIT(SPCR,CPHA,VALUE)
#define ADJ_SPR(VALUE)   MSC_PRT(SPCR,0XFC,VALUE&3);ADJ_BIT(SPSR,SPI2X,((VALUE&4)>>2))

/* SPSR Register */
enum{SPI2X,WCOL=6,SPIF};
#define GET_SPIF  GET_BIT(SPSR,SPIF)
#define GET_WCOL  GET_BIT(SPSR,WCOL)

#endif /* 01_MCAL_SPI_PRIVATE_H_ */
