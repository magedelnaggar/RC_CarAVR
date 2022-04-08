/*
 * US.h
 *
 *  Created on: Mar 31, 2022
 *      Author: abdel
 */

#ifndef HAL_ULTRASONIC_US_H_
#define HAL_ULTRASONIC_US_H_


 void ULTRASONIC_INIT(void);
 s32  ULTRASONIC_GET_DISTANCE(void);


 void INC_OV(void);


#define TCNT0	             *((volatile u8*)0x52)

#define TCCR1B 				 *((volatile u8*)0x4A)
#define ICES1 				 6
#endif /* HAL_ULTRASONIC_US_H_ */
