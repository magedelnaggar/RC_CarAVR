/*
 * TIMER0_config.h
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#ifndef MCAL_TIMER0_TIMER0_CONFIG_H_
#define MCAL_TIMER0_TIMER0_CONFIG_H_

/********_SELECT_TIMER_0_MODE_********/
/*_OPTIONS_1_-> [ NORMAL ] ***********/
/*_OPTIONS_2_-> [ PWM ] **************/
/*_OPTIONS_3_-> [ CTC ] **************/
/*_OPTIONS_4_-> [ FAST_PWM ] *********/
#define TIMER_0_MODE         NORMAL
/*************************************/

/******_SELECT_TIMER_0_PRESCALER_******/
/*_OPTIONS_1_-> [ NO_PRESCALING]  *****/
/*_OPTIONS_2_-> [ _8 ] 	***************/
/*_OPTIONS_3_-> [ _64 ] ***************/
/*_OPTIONS_4_-> [ _256 ] **************/
/*_OPTIONS_5_-> [ _1024 ] *************/
#define TIMER_0_PRESCALER    _1024
/**************************************/
#define F_OSC 					16

#endif /* MCAL_TIMER0_TIMER0_CONFIG_H_ */
