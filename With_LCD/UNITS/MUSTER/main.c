/*
 * main.c
 *
 *      Created on: Sep 12, 2023
 *      Author: 1- Abdelrahman Ashraf
 *              2- Elsayed TalAat
 */

/* ************************************ ******* ****** ******* ************************************ */
/* ************************************ ******* MASTER ******* ************************************ */
/* ************************************ ******* ****** ******* ************************************ */

/* ************************************ INCLUDES ************************************ */

#include "00_UB/STD_TYPES.h"
#include "00_UB/BIT_MATH.h"
#include "01_MCAL/DIO/DIO.h"
#include "01_MCAL/SPI/SPI.h"
#include "02_HAL/LCD/LCD.h"
#include "02_HAL/KPD/KPD.h"
#include "02_HAL/EEPROM/EEPROM.h"
#include <avr/delay.h>

/* ************************************ DEFINES ************************************ */

#define  EEPROM_STATUS_LOCATION       0x20
#define  EEPROM_PASSWORD_LOCATION1    0x21
#define  EEPROM_PASSWORD_LOCATION2    0x22
#define  EEPROM_PASSWORD_LOCATION3    0x23
#define  EEPROM_PASSWORD_LOCATION4    0x24
#define  MAX_TRIES    3                                   // Number of TRIES
#define  NO_PASS     0xff
#define  chooseSlave(VALUE)  MSC_PRT(PORTC,0X3F,VALUE<<6) // Slave0 , Slave1 , Slave2...
#define  room_num  3                                      // Number of ROOMS

/* ************************************ variables ************************************ */

u8 arr[4];                               // array for 4bits of password
u8 currentRoom;                          // chosen room
u8 currentFut;                           // chosen features
u8 roomFut [room_num][5][6]=             // features of each room
{
		{"Temp","Light","Door","TV"},    // room(1)
		{"Temp","Light","Door"},         // room(2)
		{"Light","garage"}               // garage
};
u8 roomFutNum [room_num]={4,3,2};        // Number of features

/* ============================================ MAIN CODE ============================================ */

int main(){
	/* *********************************** Initialization *********************************** */
	HCLCD_vidInit();      // Initialization LCD SCREEN
	SPI_vidInit(MASTER);  // Initialization SPI MASTER
	keybad_inti();        // Initialization KEYBAD
	/* *** */
	u8 i;
	u8 tries=MAX_TRIES;
	MSC_PRT(DDRC,0X3F,0XC0);

	/* ************************************ WELCOME ************************************ */

	HCLCD_vidGoTo(0,3);                   // Move carousel to 0 ->y , 3 ->x
	HCLCD_vidSendString("* WELCOME *",0); // Print WELCOME on LCD
	_delay_ms(250);                       // Delay
	HCLCD_vidGoTo(1,3);                   // Move carousel to 1 ->y , 3 ->x
	HCLCD_vidSendString("Smart Home",0);  // Print Smart Home on LCD
	_delay_ms(250);                       // Delay
	HCLCD_vidClear();                     // CLEAR LCD

	/* ************************************ SET Password ************************************ */
	if(EEPROM_u8readChar(0,EEPROM_STATUS_LOCATION)==NO_PASS)
	{
		HCLCD_vidSendString("Set new password:",0); // Print (Set new password:) on LCD
		HCLCD_vidGoTo(1,6);                         // Move Curser to 1 ->y , 6 ->x
		for (i=0;i<=3;i++)                          // loop to write 4 number to password
		{
			u8 value='\0';                          // value = bottons in keybad
			do
			{
				value=keybad_PressKey();           // pressed a password in keybad
			}while (value==NO_KEY);
			if (value == 'n')                      // if (value =n) rewrite password
			{
				i=-1;
				HCLCD_vidGoTo(1,6);                // Move Curser to 1 ->y , 6 ->x
				HCLCD_vidSendString("    ",0);     // Print  on LCD
				HCLCD_vidGoTo(1,6);                // Move Curser to 1 ->y , 6 ->x
			}
			else
			{
				HCLCD_vidSendData(value);          // Print new password on LCD
				_delay_ms(100);                    // Delay to return curser one step
				HCLCD_vidGoTo(1,6+i);              // Move Curser to 1 ->y , 6 ->x for 4bits
				HCLCD_vidSendData('*');            // Print * on LCD
				EEPROM_vidWriteChar(0,EEPROM_PASSWORD_LOCATION1+i,value);
			}
		}
		EEPROM_vidWriteChar(0,EEPROM_STATUS_LOCATION,0x00); // change STATUS LOCATION
	}

	/* ************************************ CHECKED Password ************************************ */

	while(1)
	{
		arr[0]=arr[1]=arr[2]=arr[3]=NO_KEY;
		HCLCD_vidClear();                             // CLEAR LCD
		HCLCD_vidSendString("Enter Password:",0);     // Print ( Enter Password:) on LCD
		HCLCD_vidGoTo(1,6);                           // Move Curser to 1 ->y , 6 ->x
		for (i=0;i<=3;i++)                            // loop to write 4 number to password
		{
			do
			{
				arr[i]=keybad_PressKey();             // pressed a number in keybad to write password
			}while (arr[i]==NO_KEY);
			if (arr[i] == 'n')                        // if (value =n) rewrite password
			{
				i=-1;
				HCLCD_vidGoTo(1,6);                   // Move Curser to 1 ->y , 6 ->x
				HCLCD_vidSendString("    ",0);        // Print     on LCD
				HCLCD_vidGoTo(1,6);                   // Move Curser to 1 ->y , 6 ->x
			}
			else
			{
				HCLCD_vidSendData(arr[i]);             // Print old password on LCD
				_delay_ms(200);                        // Delay to return curser one step
				HCLCD_vidGoTo(1,6+i);                  // Move Curser to 1 ->y , 6 ->x for 4bits
				HCLCD_vidSendData('*');                // Print * on LCD
			}
		}
		/* *********************  Right Password  ************************* */

		if(EEPROM_u8readChar(0,EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_u8readChar(0,EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_u8readChar(0,EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_u8readChar(0,EEPROM_PASSWORD_LOCATION4)==arr[3])
		{
			HCLCD_vidClear();                              // CLEAR LCD
			HCLCD_vidSendString("Right Password",0);       // Print Right Password on LCD
			_delay_ms(100);                                // Delay
			break;
		}
		/* *********************  Wrong Password  ************************* */
		else
		{
			tries=tries-1;                               // Number of tries-1    // tries=3
			if (tries>0)
			{
				HCLCD_vidClear();                             // CLEAR LCD
				HCLCD_vidSendString("Wrong Password",0);      // Print Wrong Password on LCD
				_delay_ms(500);                               // Delay
				HCLCD_vidClear();                             // CLEAR LCD
				HCLCD_vidSendString("Try Again:",0);          // Print Try Again on LCD
				HCLCD_vidSendData(tries+48);                  // Print Number of left tries on LCD
				_delay_ms(500);                               // Delay

			}
			/* *********************** fail (MAX_TRIES) times to enter the Right Password ************************* */
			else
			{
				for (s8 i = 20;i>=0;i--)                         // loop to WAIT time to try 3times more
				{
					HCLCD_vidClear();                             // CLEAR LCD
					HCLCD_vidSendString("Failed Open System",0);  // Print (Failed Open System) on LCD
					HCLCD_vidGoTo(1,6);                           // Move Curser to 1 ->y , 6 ->x
					HCLCD_vidSendNumber(i);                       //20sec // Print (WAIT of time) on LCD
					_delay_ms(900);                               // Delay
				}
			}
		}
	}
	/* ************************************ Control ************************************ */
	while (1)
	{
while1:
		HCLCD_vidClear();                            // CLEAR LCD
		HCLCD_vidSendString("Choose the room:",0);   // Print (Choose the room:) on LCD
		HCLCD_vidGoTo(1,0);                          // Move Curser to 1 ->y , 0 ->x
		u8 userData=0;
		for (u8 i=1;i<=room_num;i++)                 // loop show number of room
		{
			HCLCD_vidSendData(i+'0');                // Print number of room on LCD
			if (i!=room_num)                         // if (i!=number of room) to stop Print (,) in end
				HCLCD_vidSendData(',');              // Print (,) on LCD
		}
		HCLCD_vidSendString("  -> ",0);              // Print (  -> ) on LCD
		do
		{
			currentRoom=keybad_PressKey();           // Enter the room number
		} while (currentRoom==NO_KEY);
		if (currentRoom=='n'||currentRoom=='-')goto while1;                   //reset if 'n'
		HCLCD_vidSendData(currentRoom);              // Print (the room number) on LCD
		currentRoom-='1';                            // change from ASCII code to REAL number
		chooseSlave(currentRoom);                    // Choose Slave from (Slave0, Slave1, garage)
		_delay_ms(150);                              // Delay
feature:
		HCLCD_vidClear();                            // CLEAR LCD
		for(u8 i=0;i<roomFutNum[currentRoom];i++)    // loop to show the features of each room
		{
			if (i)HCLCD_vidSendData(' ');            // Print   on LCD
			HCLCD_vidSendData(i+1+'0');              // send number of features
			HCLCD_vidSendData(':');                  // Print : on LCD

			HCLCD_vidSendString(roomFut [currentRoom][i],0); // Print features name on LCD
			if (i==1)HCLCD_vidGoTo(1,0);            // Move Curser to 1 ->y , 0 ->x
		}
		do
		{
			currentFut=keybad_PressKey();             // Enter number of features
		} while (currentFut==NO_KEY);
		if (currentFut=='n'||currentFut=='-')goto while1;                   //reset if 'n'
		currentFut-='1';                              // change from ASCII code to REAL number
		HCLCD_vidClear();                             // CLEAR LCD

		/* ************************************ feature temperature ************************************ */

		if(currentFut==0 && ( currentRoom==0 || currentRoom==1))     // feature (1) temperature accept room1 and room2
		{
			HCLCD_vidSendString("Enter the Temp :",0); // Print (Enter the temperature) on LCD
			HCLCD_vidGoTo(1,0);                        // Move Curser to 1 ->y , 0 ->x

			for (u8 i=0;i<2;i++)                       // loop to enter the temperature 2number
			{
				u8 temperature;
				do
				{
					temperature=keybad_PressKey();        // enter the temperature
				} while (temperature==NO_KEY);
				if (temperature=='n')goto while1;                   //reset if 'n'
				if (temperature=='-')goto feature;
				HCLCD_vidSendData(temperature);           // send temperature to LCD
				userData=userData*10+((temperature)-'0'); // 3*10+2 = 32
			}// 0xxx xxxx
			// 1xxx ---y
		}
		/* ************************************ other features ************************************ */
		/* ************************ {temperature, Light, Door, TV, Garage} ************************ */

		else
		{
			HCLCD_vidSendString(roomFut [currentRoom][currentFut],0); // other features
			HCLCD_vidGoTo(1,0);                              // going to the second line
			HCLCD_vidSendString("1>ON | 0>OFF :",0);                    // Print (1-ON   0-OFF) on LCD
			do
			{
				userData=keybad_PressKey();                  // choose 0 to off or 1 to on
			} while (userData==NO_KEY);
			if (userData=='n')goto while1;                   //reset if 'n'
			if (userData=='-')goto feature;
			HCLCD_vidGoTo(1,0);                              // Move Curser to 1 ->y , 0 ->x
			HCLCD_vidSendData(userData);                     // send user choose
			userData=(userData-'0')|0X80|((currentFut)<<4);    // 1xxx---y
		}
		_delay_ms(150);                                      // Delay
		SPI_u8SendReceive(userData);                         // send choosen data to choosen slave
//		HCLCD_vidClear();                                    // CLEAR LCD
//		HCLCD_vidSendNumber(userData);                       // send number on LCD == flag checked the data send
//		_delay_ms(500);                                      // Delay
	}
	return 0;
}
/* ************************************ THE END ************************************ */
/* ==================================================================================================== */
