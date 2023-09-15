/*
 * ADC.c
 *
 *  Created on: Aug 24, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void (*ADC_prtCallBack)(void) = NULL;

void ADC_vidInit(u8 reference, u8 Adjustment, u8 pre_scaler){
	ADJ_REFS(reference);
	ADJ_ADLAR(Adjustment);
	ADJ_ADPS(pre_scaler);
	/*4. decide if auto trigger*/
	/*5. decide the Interrupting*/
	ADJ_ADEN(HIGH); // It should be the last step in Init.func.
}
u16 ADC_u16Read(u8 channel){
	ADJ_MUX(channel);
	ADJ_ADSC(HIGH);
	while(!GET_ADIF);
	CLEAR_ADIF;
	return ADC_D;
}

void ADC_vidSetCallBack(void (*ptr)(void)){
	ADC_prtCallBack = ptr;
}


void __vector_16(void) __attribute__((signal, used, externally_visible));
void __vector_16(void)
{
	ADC_prtCallBack();
}
