/*
 * main.c
 *
 *      Created on: Sep 12, 2023
 *      Author: 1- Abdelrahman Ashraf
 *              2- Elsayed TalAat
 */

/* ************************************ ******* ****** ******* ************************************ */
/* ************************************ ******* GARAGE ******* ************************************ */
/* ************************************ ******* ****** ******* ************************************ */

/* ************************************ INCLUDES ************************************ */

#include "00_UB/STD_TYPES.h"
#include "00_UB/BIT_MATH.h"
#include "01_MCAL/DIO/DIO.h"
#include "01_MCAL/GLOBAL_INT/GLOBAL_INT.h"
#include "01_MCAL/SPI/SPI.h"
#include "01_MCAL/SPI/private.h"
#include "01_MCAL/EXT_INT/EXT_INT.h"
#include "02_HAL/LCD/LCD.h"
#include "02_HAL/SERVO/SERVO.h"
#include <avr/delay.h>

/************************************** definition and variables *************************************/
u8 spaces=0X80;               // spaces is a location of cars
#define MAX_NUM    3          // MAX Number of cars
u8 carNUm;                    // Variable refer to Number of cars
/*-------------------------------*/
u8 features [3]={1,1};           // {features(2),features(3)  }
                                 // {Light      ,GARAGE State }
//u8 G_Light =1;
//u8 G_State =1;
/***************************************** functions definition **************************************/
void THE_MAIN_FUNCTION (void);      // MAIN functions into while(1) loop
void EXT_INT_FUNC0 (void);          // function to ENTRY code interrupt
void EXT_INT_FUNC1 (void);          // function to EXIT code interrupt
void SPI_FUNC (void);               // SPI function

/* ============================================ MAIN CODE ============================================ */

int main()
{
	/* ************************************* Initialization ************************************ */
	GLOBAL_INT_Enable();                                // Initialization GLOBAL INTTERUPT
	SPI_vidInit(SLAVE);                                 // Initialization SPI SLAVE
	HCLCD_vidInit();                                    // Initialization LCD Screen
	SERVO_vidInit();                                    // Initialization SERVO MOTOR

	/* **************************************  Interrupts *************************************** */
	SPI_vidInterrupt(SPI_FUNC);
	/* ****************************************** I/O ******************************************* */
	DIO_vidSetPinDirection(PORT_D,PIN_2, INPUT);         // Make pin2 portD input to ENTRY code interrupt
	DIO_vidSetPinDirection(PORT_D,PIN_3, INPUT);         // Make pin3 portD input to EXIT code interrupt
	DIO_vidSetPinDirection(PORT_D,PIN_4, OUTPUT);        // Make pin4 portD output (TIMER) to SERVO MOTOR
	DIO_vidSetPinDirection(PORT_D,PIN_7, OUTPUT);        // Make pin4 portD output SPI test digit
	MSC_PRT(DDRA,0XC7,0X00);                             // Make portA output (1100 0111), input 0
	DIO_vidSetPinDirection(PORT_A,PIN_7, OUTPUT);        // Make pin7 portA output to LAMP

	/* *************************************** definition **************************************** */
	u8 carChar0[8]={0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00};  // form space car
	u8 carChar1[8]={0x00,0x0E,0x15,0x1F,0x11,0x00,0x1F,0x00};  // form car
	HCLCD_vidSendSpecialChar(carChar0, 0);                     // show space car on LCD
	HCLCD_vidSendSpecialChar(carChar1, 1);                     // show car on LCD

	/*----------------------------------------------------*/
	SERVO_vidAngle(0);                                         // ANGLE of motor = 0
	for (u8 i=0;i<3;i++){                                      // loop to read pin3,pin4,pin5 in portA
		carNUm+=DIO_vidGetPinValue(PORT_A,3+i);                // read number of cars in garage
	}
	SPDR=0XFF;
	/* ****************************************** START ******************************************* */
	while(1)
	{
		THE_MAIN_FUNCTION ();
	}
	return 0;
}
/* ============================================ THE END CODE ============================================ */

/* ====================================== FUNCTION IMPLEMENTATION ====================================== */

/* ******************************************** THE MAIN FUNCTION ****************************************** */
void THE_MAIN_FUNCTION (void){
	u8 localSpaces = DIO_vidGetPortValue(PORT_A) &0X38;    //0011 1000
	if (localSpaces!=spaces){                              // if location Spaces != number of cars
		spaces=localSpaces;
		HCLCD_vidClear();                                  // CLEAR LCD
		HCLCD_vidGoTo(1 ,7);                               // Move Curser to 1 ->y , 7 ->x
		for (u8 i=0;i<3;i++){                              // loop to get number of cars in garage
			u8 pinValue =GET_BIT(spaces,i+3);
			HCLCD_vidSendData(pinValue);                   // send number of cars to LCD
		}

	/* ********************* Number Of Cars  ********************* */

		HCLCD_vidGoTo(0 ,0);                               // Move Curser to 0 ->y , 0 ->x
		HCLCD_vidSendString("There are ",0);               // Print (There are ) on LCD
		HCLCD_vidSendData(carNUm+'0');                     // Print number of cars on LCD
		HCLCD_vidSendString(" cars",0);                    // Print ( cars) on LCD
	}

	/* ************************* LIGHT  ************************** */

	ADJ_BIT(PORTA,PIN_7,features[0]);           // light on or off

	/* ************************* ENTRY  ************************** */

	if(DIO_vidGetPinValue(PORT_D,PIN_2)){       //  ENTRY code interrupt
		 EXT_INT_FUNC0 ();
	}

	/* ************************** EXIT  ************************** */

	if(DIO_vidGetPinValue(PORT_D,PIN_3)){        //  EXIT code interrupt
		 EXT_INT_FUNC1 ();
	}
}

/* ******************************************** EXT_INT_FUNC0 ****************************************** */

void EXT_INT_FUNC0 (void){

	/* ************************* NOT ACTIVE GARAGE ************************** */

	if (features[1]==0)                                    // feature 1-> garage == don't allow from master
	{
		HCLCD_vidClear();                                  // CLEAR LCD
		HCLCD_vidSendString("     Sorry,",0);              // Print (      Sorry,) on LCD
		HCLCD_vidGoTo(1 ,0);                               // Move Curser to 1 ->y , 0 ->x
		HCLCD_vidSendString("you can't enter",0);          // Print (you can't enter) on LCD
		_delay_ms(3000);                                   // DELAY
		spaces=0X80;
	}

	/* ************************* FULL GARAGE  ************************** */

	else if (carNUm==MAX_NUM)                              // IF spaces = number of cars
	{
		HCLCD_vidClear();                                  // CLEAR LCD
		HCLCD_vidSendString("     Sorry,",0);              // Print (      Sorry,) on LCD
		HCLCD_vidGoTo(1 ,1);                               // Move Curser to 1 ->y , 1 ->x
		HCLCD_vidSendString("Garage is full",0);           // Print (Garage is full) on LCD
		_delay_ms(3000);                                   // DELAY
		spaces=0X80;
	}

	/* ************************* ENTER CARS  ************************** */

	else
	{
		SERVO_vidAngle(90);                                // ANGLE of motor = 90
		u8 localSpaces;
		do{
		  localSpaces = DIO_vidGetPortValue(PORT_A) &0X38; //0011 1000  read number of cars
		} while(localSpaces==spaces);
		carNUm++;                                          // increase number of cars
		_delay_ms(500);                                    // DELAY
		SERVO_vidAngle(0);                                 // ANGLE of motor = 0
	}
	spaces=0X80;                                           // return
}

/* ******************************************** EXT_INT_FUNC1 ****************************************** */

void EXT_INT_FUNC1 (void)
    /* ************************* EXIT CARS  ************************** */
{
	if (carNUm>0)                                            // IF  number of cars > 0
	{
		SERVO_vidAngle(90);                                  // ANGLE of motor = 90
		u8 localSpaces;
		do{
			localSpaces = DIO_vidGetPortValue(PORT_A) &0X38; //0011 1000  read number of cars
		} while(localSpaces==spaces);
		carNUm--;                                            // decrease number of cars
		_delay_ms(500);                                      // DELAY
		SERVO_vidAngle(0);                                   // ANGLE of motor = 0
		spaces=0X80;                                         // return
	}
}

/* ******************************************** SPI_FUNC ****************************************** */
void SPI_FUNC (void){
	TOG_BIT(PORTD,7);         // TOGGLE pin7 PORTD
	u8 getValue = SPDR;
	features[((getValue&0X70)>>4)] =(getValue&1); // other features
	SPDR=0XFF;
}

/* ============================================ END FUNCTION ============================================ */

/* ============================================ THE END ============================================ */
