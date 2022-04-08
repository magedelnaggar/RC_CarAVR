/*
 * TIMER0_int.h
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#ifndef MCAL_TIMER2_TIMER2_INT_H_
#define MCAL_TIMER2_TIMER2_INT_H_


ES_t TIMER_2_enuInit     (void);
ES_t TIMER_2_enuSetTime (u32);
ES_t TIMER_2_enuStart    (void);
ES_t TIMER_2_enuStop     (void);
void Timer_2_SetCallBack(void(*Copy_pfunAppFun)(void));

#endif /* MCAL_TIMER2_TIMER0_INT_H_ */
