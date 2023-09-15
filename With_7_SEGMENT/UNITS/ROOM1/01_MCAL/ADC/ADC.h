/*
 * ADC.h
 *
 *  Created on: Aug 24, 2023
 *      Author: ar70s
 */

#ifndef _MCAL_ADC_ADC_H_
#define _MCAL_ADC_ADC_H_


/* **** ADMUX **** */
#define ADMUX  (*(volatile u8*)(0X27))     //ADC Multiplexer Selection Register
enum {MUX0,MUX1,MUX2,MUX3,MUX4,ADLAR,REFS0,REFS1}; //ADMUX bits
#define ADJ_REFS(VALUE)   MSC_PRT(ADMUX,0X3F,VALUE<<6) // RRXXXXXX
#define ADJ_ADLAR(VALUE)  ADJ_BIT(ADMUX,5,VALUE)       // XXRXXXXX
#define ADJ_MUX(VALUE)    MSC_PRT(ADMUX,0XE0,VALUE)    // XXXRRRRR
enum {AREF,AVCC,Internal2_56=3};                 //the values of REFS
enum {RIGHT,LEFT};                               //the values of ADLAR
enum {ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7};	 //the values of MUX


/* **** ADCSRA **** */

#define ADCSRA (*(volatile u8*)(0X26))     //ADC Control and Status Register A
enum {ADPS0,ADPS1,ADPS2,ADIE,ADIF,ADATE,ADSC,ADEN}; //ADCSRA bits
#define ADJ_ADEN(VALUE)   ADJ_BIT(ADCSRA,7,VALUE)    // RXXXXXXX
#define ADJ_ADSC(VALUE)   ADJ_BIT(ADCSRA,6,VALUE)    // XRXXXXXX
#define ADJ_ADATE(VALUE)  ADJ_BIT(ADCSRA,5,VALUE)    // XXRXXXXX
#define GET_ADIF          GET_BIT(ADCSRA,4)          // XXXRXXXX (get the value of ADC Interrupt Flag)
#define CLEAR_ADIF        SET_BIT(ADCSRA,4)          // XXXRXXXX (clear the ADC Interrupt Flag)
#define ADJ_ADIE(VALUE)   ADJ_BIT(ADCSRA,3,VALUE)    // XXXXRXXX
#define ADJ_ADPS(VALUE)   MSC_PRT(ADCSRA,0XF8,VALUE) // XXXXXRRR
enum {DIV_FCT2=1,DIV_FCT4,DIV_FCT8,DIV_FCT16,
	  DIV_FCT32,DIV_FCT64,DIV_FCT128};        	 //the values of ADPS


/* **** ADC Data **** */

#define ADCH    (*(volatile u8*)(0X25))     //ADCH Data Register
#define ADCL    (*(volatile u8*)(0X24))     //ADCL Data Register
#define ADC_D   (*(volatile u16*)(0X24))    //ADC Data Register


/* **** SFIOR **** */

#define SFIOR  (*(volatile u8*)(0X50))     //Special FunctionIO Register
enum {ADTS0=5,ADTS1,ADTS2}; //SFIOR bits
#define ADJ_ADTS(VALUE)   MSC_PRT(SFIOR,0X1F,VALUE<<5) // RRRXXXXX

/* **** Functions **** */

void ADC_vidInit(u8 reference,u8 Adjustment,u8 pre_scaler);
u16 ADC_u16Read(u8 channel);
void ADC_vidSetCallBack(void (*ptr)(void));

#endif /* 01_MCAL_ADC_ADC_H_ */
