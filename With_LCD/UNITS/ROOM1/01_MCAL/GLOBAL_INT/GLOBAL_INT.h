/*
 * GLOBAL_INT.h
 *
 *  Created on: Aug 24, 2023
 *      Author: ar70s
 */

#ifndef _MCAL_GLOBAL_INT_GLOBAL_INT_H_
#define _MCAL_GLOBAL_INT_GLOBAL_INT_H_

#define SREG (*(volatile u8*)0x5F)

#define I 7

void GLOBAL_INT_Enable(void);
void GLOBAL_INT_Disable(void);

#endif /* GLOBAL_INT_H_ */
