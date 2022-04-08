/*
 * TIMER0_prog.c
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER0_config.h"
#include "TIMER0_priv.h"


u32 TIMER_0_u32OverFlowNum;
u8  TIMER_0_u8PreloadVal;
void (* TIMER_0_PcallbackFun)(void) = NULL;


ES_t TIMER_0_enuInit(void)
{
	u8 LOC_enuErrorState = ES_NOK;

	#if TIMER_0_MODE == NORMAL
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);

	SET_BIT(TIMSK,TOIE0);	/* Enable Overflow interrupt */

	#elif	TIMER_0_MODE == CTC
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	SET_BIT(TIMSK,OCIE0);	/* Enable Output Compare Match  interrupt */

	#elif	TIMER_0_MODE == FAST_PWM
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);


	#elif	TIMER_0_MODE == PWM
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);

	#endif



	return LOC_enuErrorState;
}
ES_t TIMER_0_enuSetTime (u32 COPY_u8TimeInMillis){
	u8 LOC_enuErrorState = ES_NOK;

	u32 LOC_TickTime	= (TIMER_0_PRESCALER /F_OSC);
	u32 LOC_TotalTicks	= (COPY_u8TimeInMillis*1000)/ LOC_TickTime;
	TIMER_0_u32OverFlowNum = LOC_TotalTicks / 256;
	TIMER_0_u8PreloadVal= 256 - (LOC_TotalTicks % 256);
	if( (LOC_TotalTicks % 256) != 0 )
	{
		TCNT0 = TIMER_0_u8PreloadVal;
		TIMER_0_u32OverFlowNum++;
	}

	return LOC_enuErrorState;
}
ES_t TIMER_0_enuStart(void){
	u8 LOC_enuErrorState = ES_NOK;

	#if TIMER_0_PRESCALER == NO_PRESCALING
	TCCR0 |= 0x01;

	#elif	TIMER_0_PRESCALER == _8
	TCCR0 |= 0x02;

	#elif	TIMER_0_PRESCALER == _64
	TCCR0 |= 0x03;

	#elif	TIMER_0_PRESCALER == _256
	TCCR0 |= 0x04;

	#elif	TIMER_0_PRESCALER == _1024
	TCCR0 |= 0x05;
	#endif




	return LOC_enuErrorState;
}
ES_t TIMER_0_enuStop(void){
	u8 LOC_enuErrorState = ES_NOK;

	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);

	LOC_enuErrorState = ES_OK;
	return LOC_enuErrorState;
}

ISR(TIMER0_OVF_vect){


	//static u32 counter = 0 ;
	//counter++;
	/*if(counter == TIMER_0_u32OverFlowNum)
	{
		TIMER_0_PcallbackFun();
		TCNT0 = TIMER_0_u8PreloadVal;
		counter = 0;
	}*/
	TIMER_0_PcallbackFun();
}



void Timer_0_SetCallBack (void(*Copy_pfunAppFun)(void))
{
		TIMER_0_PcallbackFun = Copy_pfunAppFun;
}

