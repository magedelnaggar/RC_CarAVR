/*
 * main.c
 *
 *  Created on: Mar 31, 2022
 *      Author: maged
 */


/*includes*/
#include "../LIB/stdTypes.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../HAL/Switch/Switch_config.h"
#include "../HAL/Switch/Switch_int.h"

#include "../HAL/LCD/LCD_int.h"

#include "../HAL/Keypad/Keypad_int.h"

#include "../MCAL/EXTI/EXTI_config.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include "../MCAL/TIMER0/TIMER0_int.h"
#include "../MCAL/TIMER2/TIMER2_int.h"

#include "../MCAL/UART/UART_Interface.h"

#include "../HAL/ULTRASONIC/US.h"
#include "../HAL/HC_05/HC_05_interface.h"

#include "../MCAL/GIE/GIE_int.h"

#include <util/delay.h>

#include "../MCAL/ADC/ADC_int.h"


/* main.h*/

void Motor_Forward( void );
void Motor_Right(void);
void Motor_Left( void );
void Motor_stop( void );
void Horn_ON( void );
void Horn_OFF ( void ) ;
void Relay_TOG( void );
void Relay_ON( void );
void Relay_OFF( void );
void Waiting(void);
//void Wait(void);


#define CR_OFF			0
#define CR_ON			1
#define CR_DIS   		20		//CR distance

u8 Waiting_flag = 0;
int main(void)
{

	u8 bRead = 0;      				 //bluetooth reading
	u8 CRMode_flag = CR_OFF;
	s32 Ultra_read = 0;


	//init drivers

	//LCD
	LCD_enuInit();

	//TIMER2

	TIMER_2_enuInit();
	TIMER_2_enuSetTime(1000);
	GIE_enuEnable();
	//TIMER_2_enuStart();
	Timer_2_SetCallBack(Waiting);

	//Ultrasonic
	ULTRASONIC_INIT();

	//Bluetooth
	HC_05_Init();

	//Motor
	DIO_enuSetPinDirection(DIO_u8GROUP_C, DIO_u8PIN7 , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(DIO_u8GROUP_C, DIO_u8PIN2 , DIO_u8OUTPUT);
	DIO_enuSetPinDirection(DIO_u8GROUP_D, DIO_u8PIN3  , DIO_u8OUTPUT);
	//Relay
	DIO_enuSetPinDirection(DIO_u8GROUP_A, DIO_u8PIN2  , DIO_u8OUTPUT);
	//Horn
	DIO_enuSetPinDirection(DIO_u8GROUP_A, DIO_u8PIN3 , DIO_u8OUTPUT);

	Motor_stop();
	Horn_OFF ();
	Relay_OFF();

	LCD_enuWriteCommand(1);
	LCD_enuWriteString("CR Mode OFF");

	//Relay_ON();



	while(1)
	{

		bRead = HC_05_Receive();
		//LCD_enuGoToPosition(1,1);
		//LCD_enuWriteData(bRead);
		if('c' == bRead)   			//Waiting CRMode
		{
			if( CRMode_flag == CR_OFF)
			{
				CRMode_flag = CR_ON;
				LCD_enuWriteCommand(1);
				LCD_enuWriteString("CR Mode ON");
				_delay_ms(20);
			}
			else
			{
				CRMode_flag = CR_OFF;
				LCD_enuWriteCommand(1);
				LCD_enuWriteString("CR Mode OFF");
				_delay_ms(20);
			}
		}
		if (Waiting_flag == 1){
			TIMER_2_enuStart();
		}
		else if (Waiting_flag == 0){
			TIMER_2_enuStop();
			Relay_OFF();
		}

		// check if it CRMode or not
		if(CRMode_flag == CR_ON) //CR_MODE
		{
			Ultra_read = ULTRASONIC_GET_DISTANCE();
			_delay_ms(2);


			if(Ultra_read < CR_DIS)
			{
				Motor_Forward();
			}
			else
			{
				Motor_stop();
			}
		}
		else
		{

			switch(bRead)
			{
			case 'w':		//wait

				if (Waiting_flag == 0)
				{
					Waiting_flag = 1; //start timer
				}
				else
				{
					Waiting_flag = 0; //stop timer
					Relay_OFF();
				}
				Motor_stop();
				Horn_OFF();
				break;
			case 'l':		//Left
				Motor_Left();
				Horn_OFF();
				break;
			case 'r':		//Right
				Motor_Right();
				Horn_OFF();
				break;
			case 'f':		//forward
				Motor_Forward();
				Horn_OFF();
				break;
			case 'b':		//buzzer
				Motor_stop();
				Horn_ON();
				break;
			default :
				Motor_stop();
				Horn_OFF();
				break;
			}
		}
	}
	return 0;
}

void Motor_Forward( void )
{
	//LED1 on C7
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN7 , DIO_u8HIGH);

	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN2 , DIO_u8LOW);
	DIO_enuSetPinValue(DIO_u8GROUP_D, DIO_u8PIN3 , DIO_u8LOW);
}

void Motor_Left(void)
{
	//LED0 on C2
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN2 , DIO_u8HIGH);

	//other Stop
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN7 , DIO_u8LOW);
	DIO_enuSetPinValue(DIO_u8GROUP_D, DIO_u8PIN3 , DIO_u8LOW);
}

void Motor_Right( void )
{
	//LED2 on D3
	DIO_enuSetPinValue(DIO_u8GROUP_D, DIO_u8PIN3  , DIO_u8HIGH);

	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN7 , DIO_u8LOW);
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN2 , DIO_u8LOW);
}

void Horn_ON( void )
{
	//BUZZER on A3
	DIO_enuSetPinValue(DIO_u8GROUP_A, DIO_u8PIN3 , DIO_u8HIGH);
}

void Horn_OFF ( void )
{
	//BUZZER off A3
	DIO_enuSetPinValue(DIO_u8GROUP_A, DIO_u8PIN3 , DIO_u8LOW);
}



void Motor_stop( void )
{
	//LEDs off
	//LED1 on C7
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN7 , DIO_u8LOW);

	//LED0 on C2
	DIO_enuSetPinValue(DIO_u8GROUP_C, DIO_u8PIN2 , DIO_u8LOW);

	//LED2 on D3
	DIO_enuSetPinValue(DIO_u8GROUP_D, DIO_u8PIN3 , DIO_u8LOW);

}

void Relay_ON( void )
{
	//relay A2
	DIO_enuSetPinValue(DIO_u8GROUP_A, DIO_u8PIN2 , DIO_u8HIGH);
}
void Relay_OFF ( void )
{
	//relay A2
	DIO_enuSetPinValue( DIO_u8GROUP_A, DIO_u8PIN2 , DIO_u8LOW);
}
void  Relay_TOG( void )
{
	//BUZZER Waiting A3
	DIO_enuTogglePinValue(DIO_u8GROUP_A,DIO_u8PIN2);
}

void Waiting(void){
	Relay_TOG(); // toggle the buzzer
}
