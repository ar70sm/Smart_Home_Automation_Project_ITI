/*
 * SEV_SEG.h
 *
 *  Created on: Aug 17, 2023
 *      Author: ar70s
 */

#ifndef SEV_SEG_H_
#define SEV_SEG_H_

#define C_Cathode 0
#define C_Anode 1
#define SEV_SEG_Case C_Cathode


void SEV_SEG_vidPortInit(u8 cpu_u8Port);
void SEV_SEG_vid7Seg(u8 cpu_u8Port,u8 cpu_u8Num);
void SEV_SEG_vid2DigitNum(u8 cpu_u8Port1,u8 cpu_u8Port2,u8 cpu_u8Num);
void SEV_SEG_vidPortClose(u8 cpu_u8Port);


#endif /* SEV_SEG_H_ */
