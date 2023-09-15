/*
 * lcd.h
 *
 *  Created on: Aug 20, 2023
 *      Author: ar70s
 */

#ifndef LCD_H_
#define LCD_H_

#define lcd_data_port PORT_A
#define lcd_ctrl_port PORT_B
#define lcd_rs_pib PIN_0
#define lcd_wr_pin PIN_1
#define lcd_en_pin PIN_2


void HCLCD_vidInit(void);
void HCLCD_vidSendCommand(u8 cpy_u8Command);
void HCLCD_vidSendData(u8 cpy_u8Data);
void HCLCD_vidSendString(u8* add_pu8String,u16 cpy_u16Delay);
void HCLCD_vidSendNumber(s32 cpy_s32Number);
void HCLCD_vidSendFloat(f64 cpy_f64Float,u8 cpy_u8digit);
void HCLCD_vidGoTo(u8 cpy_u8Y ,u8 cpy_u8X);
 void HCLCD_vidClear();
 void HCLCD_vidSendSpecialChar(const u8* arr_u8Char, u8 cpy_u8BlockNumber);
 u8 HCLCD_u8GetAdress();

#endif /* LCD_H_ */
