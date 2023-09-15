/*
 * TIMER.h
 *
 *  Created on: Aug 27, 2023
 *      Author: ar70s
 */

#ifndef _MCAL_TIMER_TIMER_H_
#define _MCAL_TIMER_TIMER_H_

/* *************************************************** */
/* ****************** Timer/Counter ****************** */
#define TIMSK  (*(volatile u8*)0X59)
#define TIFR   (*(volatile u8*)0X58)


enum {TIMER2_COMP,TIMER2_OVF,
	TIMER1_CAPT,TIMER1_COMPA,
	TIMER1_COMPB,TIMER1_OVF,
	TIMER0_COMP,TIMER0_OVF
};

void TIMER_vidSetCallBack(u8 cpy_source,void (*ptr)(void));

/* ***************************************************** */
/* ****************** Timer/Counter 0 ****************** */

/* TCCR0 register */
#define TCCR0  (*(volatile u8*)0X53)
enum {CS00,CS01,CS02,WGM01,COM00,COM01,WGM00,FOC0}; // TCCR0 register bits
	#define ADJ_FOC0(VALUE) ADJ_BIT(TCCR0,7,VALUE)
	#define ADJ_WGM0(VALUE) MSC_PRT(TCCR0,0XB7,((VALUE&1)<<6)|((VALUE&2)<<2))
	#define ADJ_COM0(VALUE) MSC_PRT(TCCR0,0XCF,VALUE<<4)
	#define ADJ_CS0(VALUE)  MSC_PRT(TCCR0,0XF8,VALUE)         //adjustment the value of CS0 register
enum {Normal,PWM_PHC,CTC,F_PWM};                            // values of WGM0
enum {NON,Toggle,Clear,Set};                                // values of COM0
enum {CS0_STOP, CS0_CLK1, CS0_CLK8, CS0_CLK64, CS0_CLK256,
	CS0_CLK1024, CS0_ON_FAILLING, CS0_ON_RISING};           // values of CS0
/* Timer/Counter & Output Compare Register */
#define TCNT0  (*(volatile u8*)0X52)
#define OCR0   (*(volatile u8*)0X5C)

/* TIMSK register */
enum {TOIE0,OCIE0}; // TIMSK register bits
	#define ADJ_TOIE0(VALUE) ADJ_BIT(TIMSK,0,VALUE)
	#define ADJ_OCIE0(VALUE) ADJ_BIT(TIMSK,1,VALUE)


/* TIFR register */
enum {TOV0,OCF0}; // TIFR register bits

/* *** Functions *** */

void TIMER0_vidInit(u8 cpy_u8mode,u8 cpy_u8outMode,u8 cpy_u8prescal);
void TIMER0_vidInitNormal(u8 cpy_u8prescal);

void TIMER0_vidOvIntEnable(void);
void TIMER0_vidOvIntDisable(void);
void TIMER0_vidCmIntEnable(void);
void TIMER0_vidCmIntDisable(void);

	#define ADJ_TCNT0(VALUE) TCNT0 = VALUE
	#define ADJ_OCR0(VALUE) OCR0 = VALUE


/* ***************************************************** */
/******************** Timer/Counter 1 *******************/

/* TCCR0 register */
#define TCCR1A  (*(volatile u8*)0X4F)
#define TCCR1B  (*(volatile u8*)0X4E)
enum {WGM10,WGM11,FOC1B,FOC1A,COM1B0,COM1B1,COM1A0,COM1A1};
enum {CS10,CS11,CS12,WGM12,WGM13,ICES1=6,ICNC1};

	#define ADJ_COM1A(VALUE) MSC_PRT(TCCR1A,0X3F,VALUE<<6)
	#define ADJ_COM1B(VALUE) MSC_PRT(TCCR1A,0XCF,VALUE<<4) //#0
	#define ADJ_FOC1A(VALUE) ADJ_BIT(TCCR1A,3,VALUE)
	#define ADJ_FOC1B(VALUE) ADJ_BIT(TCCR1A,2,VALUE) // 11100111
	#define ADJ_WGM1(VALUE) MSC_PRT(TCCR1A,0XFC,(VALUE&03));MSC_PRT(TCCR1B,0XE7,((VALUE&0X0C)<<1)) //#1
	#define ADJ_ICNC1(VALUE) ADJ_BIT(TCCR1B,7,VALUE)
	#define ADJ_ICES1(VALUE) ADJ_BIT(TCCR1B,6,VALUE)
	#define ADJ_CS1(VALUE)  MSC_PRT(TCCR1B,0XF8,VALUE) //#2



/* Timer/Counter & Output Compare Register */
#define TCNT1H  (*(volatile u8*)0X4D)
#define TCNT1L  (*(volatile u8*)0X4C)
#define TCNT1  (*(volatile u16*)0X4C) // the total register

#define OCR1AH  (*(volatile u8*)0X4B)
#define OCR1AL  (*(volatile u8*)0X4A)
#define OCR1A  (*(volatile u16*)0X4A) // the total register   ##1

#define OCR1BH  (*(volatile u8*)0X49)
#define OCR1BL  (*(volatile u8*)0X48)
#define OCR1B  (*(volatile u16*)0X48) // the total register  ##2

#define ICR1H  (*(volatile u8*)0X47)
#define ICR1L  (*(volatile u8*)0X46)
#define ICR1  (*(volatile u16*)0X46) // the total register

/* TIMSK register */
enum{TOIE1=2,OCIE1B,OCIE1A,TICIE1};
	#define ADJ_TICIE1(VALUE) ADJ_BIT(TIMSK,5,VALUE)
	#define ADJ_OCIE1A(VALUE) ADJ_BIT(TIMSK,4,VALUE)
	#define ADJ_OCIE1B(VALUE) ADJ_BIT(TIMSK,3,VALUE)
	#define ADJ_TOIE1(VALUE) ADJ_BIT(TIMSK,2,VALUE)

/* TIFR register */
enum{TOV1,OCF1B,OCF1A,ICF1};

/* *** Functions *** */

void TIMER1_vidInit(u8 cpy_u8mode,u8 cpy_u8outMode,u8 cpy_u8prescal);
void TIMER1_vidInitNormal(u8 cpy_u8prescal);
void TIMER1_vidOvIntEnable(void);
void TIMER1_vidOvIntDisable(void);
void TIMER1_vidCmIntEnable(void);
void TIMER1_vidCmIntDisable(void);


/* ***************************************************** */
/******************** Timer/Counter 2 *******************/

/* TCCR2 register */
#define TCCR2  (*(volatile u8*)0X45)
enum {CS20,CS21,CS22,WGM21,COM20,COM21,WGM20,FOC2}; // TCCR2 register bits
#define ADJ_FOC2(VALUE) ADJ_BIT(TCCR2,7,VALUE)
#define ADJ_WGM2(VALUE) MSC_PRT(TCCR2,0XB7,((VALUE&1)<<6)|((VALUE&2)<<2))
#define ADJ_COM2(VALUE) MSC_PRT(TCCR2,0XCF,VALUE<<4)
#define ADJ_CS2(VALUE)  MSC_PRT(TCCR2,0XF8,VALUE)         //adjustment the value of CS0 register
enum {CS2_STOP, CS2_CLK1, CS2_CLK8, CS2_CLK32,
	CS2_CLK64, CS2_CLK128, CS2_CLK256, CS2_CLK1024};   // values of CS2
/* Timer/Counter & Output Compare Register */
#define TCNT2  (*(volatile u8*)0X44)
#define OCR2   (*(volatile u8*)0X43)

/* ASSR */
#define ASSR   (*(volatile u8*)0X42)
enum {TCR2UB ,OCR2UB, TCN2UB, AS2}; // ASSR register bits
#define ADJ_TCR2UB(VALUE) ADJ_BIT(ASSR,0,VALUE)
#define ADJ_OCR2UB(VALUE) ADJ_BIT(ASSR,1,VALUE)
#define ADJ_TCN2UB(VALUE) ADJ_BIT(ASSR,2,VALUE)
#define ADJ_AS2(VALUE)    ADJ_BIT(ASSR,3,VALUE)

/* TIMSK register */
enum {TOIE2=6 ,OCIE2}; // TIMSK register bits
#define ADJ_TOIE2(VALUE) ADJ_BIT(TIMSK,6,VALUE)
#define ADJ_OCIE2(VALUE) ADJ_BIT(TIMSK,7,VALUE)


/* TIFR register */
enum {TOV2=6,OCF2}; // TIFR register bits

/* *** Functions *** */

void TIMER2_vidInit(u8 cpy_u8mode,u8 cpy_u8outMode,u8 cpy_u8prescal);
void TIMER2_vidInitNormal(u8 cpy_u8prescal);
void TIMER2_vidOvIntEnable(void);
void TIMER2_vidOvIntDisable(void);
void TIMER2_vidCmIntEnable(void);
void TIMER2_vidCmIntDisable(void);
#define ADJ_TCNT2(VALUE) TCNT2 = VALUE
#define ADJ_OCR2(VALUE) OCR2 = VALUE

void TIMER_vidSetCallBack(u8 cpy_source,void (*ptr)(void));
#endif /* 01_MCAL_TIMER_TIMER_H_ */
