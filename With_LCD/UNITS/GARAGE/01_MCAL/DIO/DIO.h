/*
 * module name:         DIO (Digital Input Output)
 * file name:          dio.h
 * file description:   this file contains the implementation of the module
 * version:            v01
 * data:               17/8/2023
 * author:             Abd Alrahman Ashraf
 */

#ifndef DIO_H_
#define DIO_H_

/* register definition */
#define PORTA   (*(volatile u8*)0X3B)
#define DDRA    (*(volatile u8*)0X3A)
#define PINA    (*(volatile u8*)0X39)

#define PORTB   (*(volatile u8*)0X38)
#define DDRB    (*(volatile u8*)0X37)
#define PINB    (*(volatile u8*)0X36)

#define PORTC   (*(volatile u8*)0X35)
#define DDRC    (*(volatile u8*)0X34)
#define PINC    (*(volatile u8*)0X33)

#define PORTD   (*(volatile u8*)0X32)
#define DDRD    (*(volatile u8*)0X31)
#define PIND    (*(volatile u8*)0X30)

/**/

#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

#define INPUT  0
#define OUTPUT 1

#define HIGH  1
#define LOW 0

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

/**/

void DIO_vidSetPinDirection(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber, u8 cpy_u8PinDirction);
void DIO_vidSetPinValue(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber, u8 cpy_u8PinValue);
u8 DIO_vidGetPinValue(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber);
void DIO_vidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8PortDirction);
void DIO_vidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8PortValue);
u8 DIO_vidGetPortValue(u8 cpy_u8PortNumber);

#endif /* DIO_H_ */
