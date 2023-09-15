/*
 * TIMER.c
 *
 *  Created on: Aug 27, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/DIO/DIO.h"
#include "TIMER.h"

void (*prt_TIMER[8]) (void);


//#include "02_HAL/LCD/LCD.h"

/* ***** TIMER0 ***** */
void TIMER0_vidInit(u8 cpy_u8mode,u8 cpy_u8outMode,u8 cpy_u8prescal){
ADJ_WGM0(cpy_u8mode);
ADJ_COM0(cpy_u8outMode);
if (cpy_u8outMode){
	DIO_vidSetPinDirection(PORT_B,PIN_3, OUTPUT);
}
ADJ_CS0(cpy_u8prescal);
}
void TIMER0_vidInitNormal(u8 cpy_u8prescal){
ADJ_WGM0(Normal);
ADJ_CS0(cpy_u8prescal);
}

void TIMER0_vidOvIntEnable(void){
	ADJ_TOIE0(HIGH);
}
void TIMER0_vidOvIntDisable(void){
	ADJ_TOIE0(LOW);
}
void TIMER0_vidCmIntEnable(void){
	ADJ_OCIE0(HIGH);
}
void TIMER0_vidCmIntDisable(void){
	ADJ_OCIE0(LOW);
}

/* ***** TIMER1 ***** */

/* ***** TIMER2 ***** */

void TIMER2_vidInit(u8 cpy_u8mode,u8 cpy_u8outMode,u8 cpy_u8prescal){
ADJ_WGM2(cpy_u8mode);
ADJ_COM2(cpy_u8outMode);
if (cpy_u8outMode){
	DIO_vidSetPinDirection(PORT_D,PIN_7, OUTPUT);
}
ADJ_CS2(cpy_u8prescal);
}
void TIMER2_vidInitNormal(u8 cpy_u8prescal){
ADJ_WGM2(Normal);
ADJ_CS2(cpy_u8prescal);
}

void TIMER2_vidOvIntEnable(void){
	ADJ_TOIE2(HIGH);
}
void TIMER2_vidOvIntDisable(void){
	ADJ_TOIE2(LOW);
}
void TIMER2_vidCmIntEnable(void){
	ADJ_OCIE2(HIGH);
}
void TIMER2_vidCmIntDisable(void){
	ADJ_OCIE2(LOW);
}


/* ***** ALL TIMERS ***** */

void TIMER_vidSetCallBack(u8 cpy_source,void (*ptr)(void)){
	prt_TIMER[cpy_source]=ptr;
}

void __vector_4  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_5  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_6  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_7  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_8  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_9  (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_10 (void) __attribute__ ((signal,used, externally_visible)) ;\
void __vector_11 (void) __attribute__ ((signal,used, externally_visible)) ;\

void __vector_4  (void){
	prt_TIMER[0]();
}
void __vector_5  (void){
	prt_TIMER[1]();
}
void __vector_6  (void){
	prt_TIMER[2]();
}
void __vector_7  (void){
	prt_TIMER[3]();
}
void __vector_8  (void){
	prt_TIMER[4]();
}
void __vector_9  (void){
	prt_TIMER[5]();
}
void __vector_10 (void){
	prt_TIMER[6]();
}
void __vector_11 (void){
	prt_TIMER[7]();
}

