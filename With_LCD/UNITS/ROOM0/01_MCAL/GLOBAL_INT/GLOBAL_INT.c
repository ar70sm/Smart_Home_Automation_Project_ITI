/*
 * GLOBAL_INT.c
 *
 *  Created on: Aug 24, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "GLOBAL_INT.h"

void GLOBAL_INT_Enable(void){
	SET_BIT(SREG,I);
}
void GLOBAL_INT_Disable(void){
	CLR_BIT(SREG,I);
}

