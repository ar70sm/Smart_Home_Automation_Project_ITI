/*
 * main.c
 *
 *      Created on: Sep 12, 2023
 *      Author: 1- Abdelrahman Ashraf
 *              2- Elsayed TalAat
 */

/* ************************************ ******* ***** ******* ************************************ */
/* ************************************ ******* ROOM1 ******* ************************************ */
/* ************************************ ******* ***** ******* ************************************ */

/* ************************************ INCLUDES ************************************ */

#include "00_UB/STD_TYPES.h"
#include "00_UB/BIT_MATH.h"
#include "01_MCAL/DIO/DIO.h"
#include "01_MCAL/GLOBAL_INT/GLOBAL_INT.h"
#include "01_MCAL/SPI/SPI.h"
#include "01_MCAL/SPI/private.h"
#include "01_MCAL/TIMER/TIMER.h"
#include "01_MCAL/ADC/ADC.h"
#include "02_HAL/SEV_SEG/SEV_SEG.h"
#include "02_HAL/SERVO/SERVO.h"
#include <avr/delay.h>

/************************************** definition and variables *************************************/

#define  step   0.06836          // the step of the sensor
u16 value;                       // the value which gotten from the sensor
f32 temp;			             // The temperature expressed by the sensor reading
#define  range  2                // range = [(least)temperature-2 : (most) temperature+2]
u8  seg  =0;                     // The number of the 7SEG unit that is being written now
u32 msec =0;	                 // counter of the timer
/*-------------------------------*/
u8 userTemp =20;                 // value of temperature choose
u8 features [3]={0,0};           // {features(2),features(3)}
                                 //  {LIGHT     ,DOOR       }


/***************************************** functions definition **************************************/
void THE_MAIN_FUNCTION (void);
void SPI_FUNC (void);
void TIMER0_FUNC (void);
void SEV_SEG_FUNC (void);

/* ============================================ MAIN CODE ============================================ */

int main()
{
	/* ************************************* Initialization ************************************ */
	GLOBAL_INT_Enable();                          // Initialization GLOBAL INTTERUPT
	SPI_vidInit(SLAVE);                           // Initialization SPI SLAVE
	TIMER0_vidInit(F_PWM,Clear,CS0_CLK8);         // Initialization TIMER0
	ADC_vidInit(AREF,RIGHT,DIV_FCT128);           // Initialization ADC
	SEV_SEG_vidPortInit(PORT_C);                  // Initialization 7-segment
	SERVO_vidInit();                              // Initialization SERVO MOTOR

	/* **************************************  Interrupts *************************************** */
	SPI_vidInterrupt(SPI_FUNC);
	TIMER_vidSetCallBack(TIMER0_OVF,&TIMER0_FUNC);
	TIMER0_vidOvIntEnable();

	/* ****************************************** I/O ******************************************* */
	DIO_vidSetPortDirection(PORT_D,0XFF);   // PORTD OUTPUT
	MSC_PRT(DDRB,0XFC,0X03);     // 1111 1100
	MSC_PRT(DDRA,0X3F,0XC0);     // 0011 1111
	/*----------------------------------------------------*/
	SERVO_vidAngle(0);           // ANGLE of motor = 0
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
	value = ADC_u16Read(ADC0);     // convert value from analog to digital
	temp =step*value*7.114;        // The value of temperature == 0.06836 * value * 7.114

	/* ********************** ALARME ********************** */

	if (temp>((70+userTemp)/2))    // if temperature > (70+The value)/2
	{
		ADJ_BIT(PORTD,5,1);        // ALARME HIGH
	}
	else
	{
		ADJ_BIT(PORTD,5,0);        // ALARME LOW
	}

	/* ********************** AIR Condition ********************** */

	if (temp>(userTemp+range))     // if temperature > (most) temperature user +2
	{
		MSC_PRT(PORTB,0XFC,0X01);  // AIR Condition  HIGH
		u8 comp = 100+(((temp-userTemp-range)*156)/(70-range-userTemp));
		OCR0=comp;
	}

	/* ************************* COLLER ************************** */

	else if (temp<(userTemp-range)) // if temperature > (LEAST) temperature user -2
	{
		MSC_PRT(PORTB,0XFC,0X02); // COLLER  HIGH
		u8 comp = 256-(temp*156/(userTemp-range));
		OCR0=comp;
	}
	else
	{
		MSC_PRT(PORTB,0XFC,0X00); //  LOW of COLLER and AIR Condition
	}

	/* ************************* DOOR ************************** */

	if (features[1])
		SERVO_vidAngle(90);       // OPEN DOOR
	else
		SERVO_vidAngle(0);        // CLOSE DOOR

	/* ***************** The Rest Of The Features ****************** */

	ADJ_BIT(PORTA,7,features[0]); // LAMP1    OUTPUT

}
/* ******************************************** FUNCTION SPI ****************************************** */

void SPI_FUNC (void)          // IMPLEMENTATION SPI
{        
	TOG_BIT(PORTD,7);         // TOGGLE pin7 PORTD
	u8 getValue = SPDR;
	if ((getValue&0X80)==0)
		userTemp=getValue;   // User temperature
	else  /// 1xxx---t
		features[(((getValue&0X70)-1)>>4)] =(getValue&0X01); // other features
	_delay_ms(10);            // Delay
	SPDR=0XFF;
}
/* ******************************************** FUNCTION TIMER0 ****************************************** */

void TIMER0_FUNC (void)       // IMPLEMENTATION TIMER0
{
	if(!msec)SEV_SEG_FUNC (); 
	msec=(msec+1)%50;
}

/* ******************************************* FUNCTION 7-SEGMANT ****************************************** */

void SEV_SEG_FUNC (void)             // IMPLEMENTATION  7-SEGMANT
{
	u8 xx[]={0X0E,0X0D,0X0B,0X07};   // ARRAY of 4 7-SEGMANT
	MSC_PRT(PORTD,0XF0,xx[seg]) ;
	u32 num = temp*100;           
	if (seg==0){                     // 7-SEGMANT(0)
		num /=1000;
	}
	else if (seg==1){                // 7-SEGMANT(1)
		num%=1000;
		num/=100;
	}
	else if (seg==2){                // 7-SEGMANT(2)
		num%=100;
		num/=10;
	}
	else if (seg==3){                // 7-SEGMANT(3)
		num %=10;
	}
	SEV_SEG_vid7Seg(PORT_C,num);     // show numbers at 7-SEGMANT
	if (seg==1)DIO_vidSetPinValue(PORT_C,7, 1);
		seg = ((seg+1)%4);
}
/* ============================================ END FUNCTION ============================================ */

/* ============================================ THE END ============================================ */
