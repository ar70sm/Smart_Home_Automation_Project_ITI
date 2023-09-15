/*
 * module name:        DIO (Digital Input Output)
 * file name:          dio.c
 * file description:   this file contains the implementation of the module
 * version:            v01
 * data:               17/8/2023
 * author:             Abd Alrahman Ashraf
 */

#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "DIO.h"

void DIO_vidSetPinDirection(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber, u8 cpy_u8PinDirction){
	switch (cpy_u8PinDirction){
	case INPUT:
		switch (cpy_u8PortNumber){
		case PORT_A:
			CLR_BIT(DDRA,cpy_u8PinNumber);
			break;
		case PORT_B:
			CLR_BIT(DDRB,cpy_u8PinNumber);
			break;
		case PORT_C:
			CLR_BIT(DDRC,cpy_u8PinNumber);
			break;
		case PORT_D:
			CLR_BIT(DDRD,cpy_u8PinNumber);
			break;
		default :
			/*Error*/
			break;
		}
		break;
	case OUTPUT:
		switch (cpy_u8PortNumber){
		case PORT_A:
			SET_BIT(DDRA,cpy_u8PinNumber);
			break;
		case PORT_B:
			SET_BIT(DDRB,cpy_u8PinNumber);
			break;
		case PORT_C:
			SET_BIT(DDRC,cpy_u8PinNumber);
			break;
		case PORT_D:
			SET_BIT(DDRD,cpy_u8PinNumber);
			break;
		default :
			/*Error*/
			break;
		}
		break;
	default :
		/*Error*/
		break;

	}
}

void DIO_vidSetPinValue(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber, u8 cpy_u8PinValue){
	switch (cpy_u8PinValue){
	case LOW:
		switch (cpy_u8PortNumber){
		case PORT_A:
			CLR_BIT(PORTA,cpy_u8PinNumber);
			break;
		case PORT_B:
			CLR_BIT(PORTB,cpy_u8PinNumber);
			break;
		case PORT_C:
			CLR_BIT(PORTC,cpy_u8PinNumber);
			break;
		case PORT_D:
			CLR_BIT(PORTD,cpy_u8PinNumber);
			break;
		default :
			/*Error*/
			break;
		}
		break;
	case HIGH:
		switch (cpy_u8PortNumber){
		case PORT_A:
			SET_BIT(PORTA,cpy_u8PinNumber);
			break;
		case PORT_B:
			SET_BIT(PORTB,cpy_u8PinNumber);
			break;
		case PORT_C:
			SET_BIT(PORTC,cpy_u8PinNumber);
			break;
		case PORT_D:
			SET_BIT(PORTD,cpy_u8PinNumber);
			break;
		default :
			/*Error*/
			break;
		}
		break;
	default :
		/*Error*/
		break;

	}

}

u8 DIO_vidGetPinValue(u8 cpy_u8PortNumber,u8 cpy_u8PinNumber){
	u8 cop_return;
	switch (cpy_u8PortNumber){
	case PORT_A:
		cop_return = GET_BIT(PINA,cpy_u8PinNumber);
		break;
	case PORT_B:
		cop_return = GET_BIT(PINB,cpy_u8PinNumber);
		break;
	case PORT_C:
		cop_return = GET_BIT(PINC,cpy_u8PinNumber);
		break;
	case PORT_D:
		cop_return = GET_BIT(PIND,cpy_u8PinNumber);
		break;
	default :
		cop_return =-1;
		break;
	}
	return cop_return;

}

void DIO_vidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8PortDirction){
	switch (cpy_u8PortNumber){
	case PORT_A:
		DDRA = cpy_u8PortDirction;
		break;
	case PORT_B:
		DDRB = cpy_u8PortDirction;
		break;
	case PORT_C:
		DDRC = cpy_u8PortDirction;
		break;
	case PORT_D:
		DDRD = cpy_u8PortDirction;
		break;
	default :
		/*Error*/
		break;
	}
}
void DIO_vidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8PortValue){
	switch (cpy_u8PortNumber){
	case PORT_A:
		PORTA = cpy_u8PortValue;
		break;
	case PORT_B:
		PORTB = cpy_u8PortValue;

		break;
	case PORT_C:
		PORTC = cpy_u8PortValue;
		break;
	case PORT_D:
		PORTD = cpy_u8PortValue;
		break;
	default :
		/*Error*/
		break;
	}

}
u8 DIO_vidGetPortValue(u8 cpy_u8PortNumber){
	u8 cop_return;
	switch (cpy_u8PortNumber){
	case PORT_A:
		cop_return = PINA;
		break;
	case PORT_B:
		cop_return = PINB;
		break;
	case PORT_C:
		cop_return = PINC;
		break;
	case PORT_D:
		cop_return = PIND;
		break;
	default :
		/*Error*/
		break;
	}
	return cop_return;
}
