/*
 * SERVO.c
 *
 *  Created on: Sep 12, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/DIO/DIO.h"
#include "../../01_MCAL/TIMER/TIMER.h"
#include "SERVO.h"

void SERVO_vidInit(){

 ADJ_WGM1(0XF);
 ADJ_CS1(0X2);
 ADJ_COM1B(0X2);
 OCR1A  =19999;
}
void SERVO_vidAngle(u8 angle){
 OCR1B=1000+(((u32)999*angle)/180);
}

