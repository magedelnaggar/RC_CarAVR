/*
 * TIMER0_priv.h
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#ifndef MCAL_TIMER0_TIMER0_PRIV_H_
#define MCAL_TIMER0_TIMER0_PRIV_H_

/*  Timer0 Registers define */
#define TCCR0		         *((volatile u8*)0x53)
#define FOC0 		         7
#define WGM00		         6
#define COM01		         5
#define COM00 		         4
#define WGM01 		         3
#define CS02 		         2
#define CS01 		         1
#define CS00		         0



#define TCNT0	             *((volatile u8*)0x52)
#define	OCR0	             *((volatile u8*)0x5c)


#define TIMSK	             *((volatile u8*)0x59)
#define OCIE0		         1
#define TOIE0		         0



#define TIFR		         *((volatile u8*)0x58)
#define OCF0 		         1
#define TOV0		         0



#define NORMAL               0
#define PWM                  1
#define CTC                  2
#define FAST_PWM             3

#define NO_PRESCALING        1
#define _8        			 8
#define _64         	     64
#define _256     		     256
#define _1024  			     1024


#define ISR(vect_num)		void vect_num(void)__attribute__((signal));\
							void vect_num(void)

#define TIMER0_OVF_vect		__vector_11

#endif /* MCAL_TIMER0_TIMER0_PRIV_H_ */
