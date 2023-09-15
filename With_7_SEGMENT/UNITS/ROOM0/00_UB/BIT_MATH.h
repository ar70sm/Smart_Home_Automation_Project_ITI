/*
 * BIT_MATH.h
 *
 *  Created on: Jan 28, 2023
 *      Author: aminz
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BITNO)        (VAR|=(1<<BITNO))
#define CLR_BIT(VAR,BITNO)        (VAR&=(~(1<<BITNO)))
#define TOG_BIT(VAR,BITNO)        (VAR^=(1<<BITNO))
#define GET_BIT(VAR,BITNO)        ((VAR>>BITNO)&0x01)
#define MSC_PRT(VAR,MASK,VALUE)   (VAR=((VAR&(MASK))|(VALUE)))
#define ADJ_BIT(VAR,BITNO,VALUE)  MSC_PRT(VAR,(~(1<<BITNO)),(VALUE<<BITNO))

#define HIGH 1
#define LOW 0

#endif /* BIT_MATH_H_ */
