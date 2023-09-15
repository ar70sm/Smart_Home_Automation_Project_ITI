/*
 * lcd.c
 *
 *  Created on: Aug 20, 2023
 *      Author: ar70s
 */
#include "../../00_UB/STD_TYPES.h"
#include "../../00_UB/BIT_MATH.h"
#include "../../01_MCAL/DIO/DIO.h"
#include "LCD.h"
#include <avr/delay.h>


void HCLCD_vidSendCommand(u8 cpy_u8Command){
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_rs_pib,LOW);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_wr_pin,LOW);
	DIO_vidSetPortValue(lcd_data_port,cpy_u8Command);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,LOW);
	_delay_ms(3);
}
void HCLCD_vidSendData(u8 cpy_u8Data){
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_rs_pib,HIGH);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_wr_pin,LOW);
	DIO_vidSetPortValue(lcd_data_port,cpy_u8Data);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,LOW);
	_delay_ms(3);
}
void HCLCD_vidInit(void){
	DIO_vidSetPinDirection(lcd_ctrl_port,lcd_rs_pib,OUTPUT);
	DIO_vidSetPinDirection(lcd_ctrl_port,lcd_wr_pin,OUTPUT);
	DIO_vidSetPinDirection(lcd_ctrl_port,lcd_en_pin,OUTPUT);
	DIO_vidSetPortDirection(lcd_data_port,0xff);
	_delay_ms(30);
	HCLCD_vidSendCommand(0b111000);
	HCLCD_vidSendCommand(0b1100);
	HCLCD_vidSendCommand(0b1);
	HCLCD_vidSendCommand(0b110);
}
void HCLCD_vidSendString(u8* add_pu8String, u16 cpy_u16Delay){
	u8 i=0;
	while (add_pu8String[i++]){
//		if (i==17)HCLCD_vidGoTo(1,0);
// 		else if (i==33)break;
		HCLCD_vidSendData(add_pu8String[i-1]);
		_delay_ms(cpy_u16Delay);
	}
}
void HCLCD_vidSendNumber(s32 cpy_s32Number){
	if (cpy_s32Number<0){
		HCLCD_vidSendData('-');
		cpy_s32Number*=-1;
	}
	if (cpy_s32Number==0){
		HCLCD_vidSendData('0');
	}
	u32 power = 1;
	u32 cpy_u32num =cpy_s32Number;
	while(cpy_u32num){
		cpy_u32num/=10;
		power*=10;
	}
	power/=10;
	while (power){
		HCLCD_vidSendData((cpy_s32Number/power)+'0');
		cpy_s32Number%=power;
		power/=10;
	}
}

void HCLCD_vidSendFloat(f64 cpy_f64Float,u8 cpy_u8digit){
	if (cpy_f64Float<0){
		HCLCD_vidSendData('-');
		cpy_f64Float*=-1;
	}
	if ((u64)cpy_f64Float==0){
		HCLCD_vidSendData('0');
	}
	u32 floatPower=1;
	while(cpy_u8digit){
		floatPower*=10;
		cpy_u8digit--;
	}
	u32 power = 1;
	u64 cpy_u32num =cpy_f64Float;
	u8 dot=0;
	while(cpy_u32num){
		cpy_u32num/=10;
		power*=10;
		dot++;
	}
	cpy_u32num=cpy_f64Float*floatPower;
	if (((cpy_f64Float*floatPower)-cpy_u32num)>=0.5)cpy_u32num++;
	power*=floatPower/10;
	while (cpy_u32num){
		if (0==dot--){
			HCLCD_vidSendData('.');
		}
		HCLCD_vidSendData((cpy_u32num/power)+'0');
		cpy_u32num%=power;
		power/=10;
	}

}
void HCLCD_vidGoTo(u8 cpy_u8Y ,u8 cpy_u8X){
	if (cpy_u8Y==0){
		HCLCD_vidSendCommand(0x80+cpy_u8X);
	}
	else {
		HCLCD_vidSendCommand(0xc0+cpy_u8X);
	}

}
void HCLCD_vidClear(void){
	 HCLCD_vidSendCommand(1);
}
void HCLCD_vidSendSpecialChar(const u8* arr_u8Char, u8 cpy_u8BlockNumber){
	u8 cop_address = HCLCD_u8GetAdress();
	HCLCD_vidSendCommand(0x40+cpy_u8BlockNumber*8);
	for (u8 i=0;i<7;i++){
		HCLCD_vidSendData(arr_u8Char[i]);
	}
	HCLCD_vidGoTo(0,cop_address);
}

u8 HCLCD_u8GetAdress(){
	DIO_vidSetPortDirection(lcd_data_port,0x80);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_rs_pib,LOW);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_wr_pin,HIGH);
	DIO_vidSetPinValue(lcd_data_port,7,HIGH);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,HIGH);
	u8 copy_return = DIO_vidGetPortValue (lcd_data_port) - 0x80;
	_delay_ms(1);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,LOW);
	_delay_ms(2);
	DIO_vidSetPinValue(lcd_data_port,7,LOW);
	DIO_vidSetPortDirection(lcd_data_port,0xff);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(lcd_ctrl_port,lcd_en_pin,LOW);
	_delay_ms(2);
	return copy_return;
}
