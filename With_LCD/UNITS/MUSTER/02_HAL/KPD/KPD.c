/*
 * KPD.c
 *
 *  Created on: Aug 21, 2023
 *      Author: ar70s
 */
#include "../../00_UB/BIT_MATH.h"
#include "../../00_UB/STD_TYPES.h"
#include "KPD.h"
#include <avr/delay.h>
#include "../../01_MCAL/DIO/DIO.h"



u8 KPD_arr[4][4]={
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'n','0','=','+'}

};

void keybad_inti(void)
{
	DIO_vidSetPortDirection(k_port,0x0f);
	DIO_vidSetPortValue(k_port,0xff);
}

u8 keybad_PressKey(void)
{
    u8 pressed_key =NO_KEY; //'O'
    for(u8 row=0;row<4;row++)
    {
    	DIO_vidSetPinValue(k_port,row,LOW);
       for(u8 col =0;col<4;col++)
       {       //MDIO_vidGetPinValue(k_port,(col+4),&buffer);
    	   if(DIO_vidGetPinValue(k_port,(col+4))==0)//if(buffer==0)
    	   {
    		   pressed_key= KPD_arr[row][col];
    	   }
    	   while(DIO_vidGetPinValue(k_port,col+4)==0){}
    	   _delay_ms(1);
       }

       DIO_vidSetPinValue(k_port,row,HIGH);
    }
    return pressed_key;
}


