/*
 * TIMER0_prog.c
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER2_config.h"
#include "TIMER2_priv.h"


u32 TIMER_2_u32OverFlowNum;
u8  TIMER_2_u8PreloadVal;
void (* TIMER_2_PcallbackFun)(void) = NULL;


ES_t TIMER_2_enuInit(void)
{
	u8 LOC_enuErrorState = ES_NOK;

#if TIMER_2_MODE == NORMAL
	CLR_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);

	SET_BIT(TIMSK,TOIE2);	/* Enable Overflow interrupt */

#elif	TIMER_2_MODE == CTC
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);

	SET_BIT(TIMSK,OCIE2);	/* Enable Output Compare Match  interrupt */

#elif	TIMER_2_MODE == FAST_PWM
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);


#elif	TIMER_2_MODE == PWM
	SET_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);

#endif



	return LOC_enuErrorState;
}
ES_t TIMER_2_enuSetTime (u32 COPY_u8TimeInMillis){
	u8 LOC_enuErrorState = ES_NOK;

	u32 LOC_TickTime	= TIMER_2_PRESCALER /F_OSC;
	u32 LOC_TotalTicks	= (COPY_u8TimeInMillis*5000) / LOC_TickTime;
	TIMER_2_u32OverFlowNum = LOC_TotalTicks / 256;
	TIMER_2_u8PreloadVal= 256 - (LOC_TotalTicks % 256);
	if( (LOC_TotalTicks % 256) != 0 )
	{
		TCNT2 = TIMER_2_u8PreloadVal;
		TIMER_2_u32OverFlowNum++;
	}

	return LOC_enuErrorState;
}
ES_t TIMER_2_enuStart(void){
	u8 LOC_enuErrorState = ES_NOK;

#if TIMER_2_PRESCALER == NO_PRESCALING
	TCCR2 |= 0x01;

#elif	TIMER_2_PRESCALER == _8
	TCCR2 |= 0x02;

#elif	TIMER_2_PRESCALER == _64
	TCCR2 |= 0x03;

#elif	TIMER_2_PRESCALER == _256
	TCCR2 |= 0x04;

#elif	TIMER_2_PRESCALER == _1024
	TCCR2 |= 0x05;
#endif




	return LOC_enuErrorState;
}
ES_t TIMER_2_enuStop(void){
	u8 LOC_enuErrorState = ES_NOK;

	CLR_BIT(TCCR2,0);
	CLR_BIT(TCCR2,1);
	CLR_BIT(TCCR2,2);

	LOC_enuErrorState = ES_OK;
	return LOC_enuErrorState;
}

ISR(TIMER2_OVF_vect){


	static u32 counter = 0 ;
	counter++;
	if(counter == TIMER_2_u32OverFlowNum)
	{
		TIMER_2_PcallbackFun();
		TCNT2 = TIMER_2_u8PreloadVal;
		counter = 0;
	}

}



void Timer_2_SetCallBack (void(*Copy_pfunAppFun)(void))
{
	TIMER_2_PcallbackFun = Copy_pfunAppFun;
}

