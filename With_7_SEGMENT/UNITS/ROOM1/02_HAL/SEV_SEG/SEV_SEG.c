/*
 * SEV_SEG.c
 *
 *  Created on: Aug 17, 2023
 *      Author: ar70s
 */

#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/DIO/DIO.h"
#include "SEV_SEG.h"
#include "avr/delay.h"



void SEV_SEG_vidPortInit(u8 cpu_u8Port){
	switch (cpu_u8Port){
	case PORT_A: DDRA =0xff; break;
	case PORT_B: DDRB =0xff; break;
	case PORT_C: DDRC =0xff; break;
	case PORT_D: DDRD =0xff; break;
	default : /*Error*/ break;
	}
}
void SEV_SEG_vid7Seg(u8 cpu_u8Port,u8 cpu_u8Num){
	u8 ssd_num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	switch(SEV_SEG_Case){
	case C_Cathode:
		switch (cpu_u8Port){
		case PORT_A: PORTA =ssd_num[cpu_u8Num]; break;
		case PORT_B: PORTB =ssd_num[cpu_u8Num]; break;
		case PORT_C: PORTC =ssd_num[cpu_u8Num]; break;
		case PORT_D: PORTD =ssd_num[cpu_u8Num]; break;
		default : /*Error*/ break;
		}
		break;
	case C_Anode:
		switch ( cpu_u8Port){
		case PORT_A: PORTA =!ssd_num[cpu_u8Num]; break;
		case PORT_B: PORTB =!ssd_num[cpu_u8Num]; break;
		case PORT_C: PORTC =!ssd_num[cpu_u8Num]; break;
		case PORT_D: PORTD =!ssd_num[cpu_u8Num]; break;
		default : /*Error*/ break;
		}

		break;
	default:
		break;
	}

}
void SEV_SEG_vid2DigitNum(u8 cpu_u8Port1,u8 cpu_u8Port2,u8 cpu_u8Num){
	SEV_SEG_vid7Seg(cpu_u8Port2,cpu_u8Num%10);
	cpu_u8Num/=10;
	SEV_SEG_vid7Seg(cpu_u8Port1,cpu_u8Num%10);
}
void SEV_SEG_vidPortClose(u8 cpu_u8Port){
	switch (cpu_u8Port){
	case PORT_A: DDRA =0x00; break;
	case PORT_B: DDRB =0x00; break;
	case PORT_C: DDRC =0x00; break;
	case PORT_D: DDRD =0x00; break;
	default : /*Error*/ break;
	}

}

