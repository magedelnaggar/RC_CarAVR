/*
 * TIMER0_int.h
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#ifndef MCAL_TIMER0_TIMER0_INT_H_
#define MCAL_TIMER0_TIMER0_INT_H_


ES_t TIMER_0_enuInit     (void);
ES_t TIMER_0_enuSetTime (u32);
ES_t TIMER_0_enuStart    (void);
ES_t TIMER_0_enuStop     (void);
void Timer_0_SetCallBack(void(*Copy_pfunAppFun)(void));

#endif /* MCAL_TIMER0_TIMER0_INT_H_ */
