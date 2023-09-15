/*
 * EXT_INT.c
 *
 *  Created on: Aug 24, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/GLOBAL_INT/GLOBAL_INT.h"

#include "EXT_INT.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void (*EXT_INT0_CALLBACK_PTR)(void)=NULL ;
void (*EXT_INT1_CALLBACK_PTR)(void)=NULL ;
void (*EXT_INT2_CALLBACK_PTR)(void)=NULL ;

void EXT_INT_VID_ENABLE(u8 interrupt_number) //EXT0   EXT1  EXT2
{
	switch(interrupt_number)
	{
	case EXTI0:
		SET_BIT(GICR,INT0);
		break;
	case EXTI1:
		SET_BIT(GICR,INT1);
		break;
	case EXTI2:
		SET_BIT(GICR,INT2);
		break;
	}
}
void EXT_INT_VID_DISABLE(u8 interrupt_number)
{
	switch(interrupt_number)
	{
	case EXTI0:
		CLR_BIT(GICR,INT0);
		break;
	case EXTI1:
		CLR_BIT(GICR,INT1);
		break;
	case EXTI2:
		CLR_BIT(GICR,INT2);
		break;
	}

}
//   EXT0         FALLING   LOW LEVEL
void EXT_INT_VID_SET_MODE(u8 interrupt_number , u8 mode)
{
	switch(interrupt_number)
	{
	case EXTI0:
		switch(mode)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
		case IOC:
			CLR_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		case FALLING_EDGE:
			SET_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCR,ISC00);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		}
		break;
		case EXTI1:
			switch(mode)
			{
			case LOW_LEVEL:
				CLR_BIT(MCUCR,ISC11);
				CLR_BIT(MCUCR,ISC10);
				break;
			case IOC:
				CLR_BIT(MCUCR,ISC11);
				SET_BIT(MCUCR,ISC10);
				break;
			case FALLING_EDGE:
				SET_BIT(MCUCR,ISC11);
				CLR_BIT(MCUCR,ISC10);
				break;
			case RISING_EDGE:
				SET_BIT(MCUCR,ISC11);
				SET_BIT(MCUCR,ISC10);
				break;
			}

			break;
			case EXTI2:
				switch(mode)
				{
				case FALLING_EDGE:
					CLR_BIT(MCUCSR,ISC2);
					break;
				case RISING_EDGE:
					SET_BIT(MCUCSR,ISC2);
					break;
				}

				break;
	}
}



void EXT_INT0_VID_SET_CALL_BACK(void (*PTR)(void))
{
	EXT_INT0_CALLBACK_PTR=PTR;
}
void EXT_INT1_VID_SET_CALL_BACK(void (*PTR)(void))
{
	EXT_INT1_CALLBACK_PTR=PTR;
}
void EXT_INT2_VID_SET_CALL_BACK(void (*PTR)(void))
{
	EXT_INT2_CALLBACK_PTR=PTR;
}









void __vector_1 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_1 (void){
	EXT_INT0_CALLBACK_PTR();
}

void __vector_2 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_2 (void){
	EXT_INT1_CALLBACK_PTR();
}


void __vector_3 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_3 (void){
	EXT_INT2_CALLBACK_PTR();

}

