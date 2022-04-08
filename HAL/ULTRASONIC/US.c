/*
 * US.c
 *
 *  Created on: Mar 31, 2022
 *      Author: abdel
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/BIT_MATH.h"


#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIMER0/TIMER0_int.h"
#include "../../MCAL/GIE/GIE_int.h"

#include <util/delay.h>

#include "US.h"
#include "USconfig.h"



u32 Over_flow_num =0;

void ULTRASONIC_INIT(void)
{

	DIO_enuSetPinDirection(TRIGGER_GR,TRIGGER_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(ECHO_GR,ECHO_PIN,DIO_u8INPUT);
	DIO_enuSetPinValue(ECHO_GR,ECHO_PIN,DIO_u8PULL_UP);

	GIE_enuEnable();
	TIMER_0_enuInit();
	Timer_0_SetCallBack(INC_OV);

}
s32  ULTRASONIC_GET_DISTANCE(void)
{
	u8 Rising_Falling_Detect;
	f32 total_time = 0;
	f32 distance =0;
	// clearing Timer
	DIO_enuSetPinValue(TRIGGER_GR,TRIGGER_PIN,DIO_u8LOW);
	_delay_us(15);

	DIO_enuSetPinValue(TRIGGER_GR,TRIGGER_PIN,DIO_u8HIGH);
	_delay_us(15);

	DIO_enuSetPinValue(TRIGGER_GR,TRIGGER_PIN,DIO_u8LOW);


	DIO_enuGetPinValue(ECHO_GR,ECHO_PIN,&Rising_Falling_Detect);

	if(Rising_Falling_Detect == 0){

		while(Rising_Falling_Detect == 0){ // wait until it goes high
			DIO_enuGetPinValue(ECHO_GR,ECHO_PIN,&Rising_Falling_Detect);
		}
	}

	TCNT0 = 0;
	Over_flow_num = 0;

	TIMER_0_enuStart();

	while(Rising_Falling_Detect == 1){
		DIO_enuGetPinValue(ECHO_GR,ECHO_PIN,&Rising_Falling_Detect);
	}

	TIMER_0_enuStop();

	total_time = (TCNT0 + Over_flow_num *256) * (1024/16.0);

	distance = (total_time * .0344)/2 ;

	return distance ;
}


void INC_OV(void){
	Over_flow_num++;
}




