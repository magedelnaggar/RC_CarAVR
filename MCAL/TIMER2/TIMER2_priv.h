/*
 * TIMER0_priv.h
 *
 *  Created on: Mar 26, 2022
 *      Author: abdel
 */

#ifndef MCAL_TIMER2_TIMER2_PRIV_H_
#define MCAL_TIMER2_TIMER2_PRIV_H_

/*  Timer0 Registers define */
#define TCCR2		         *((volatile u8*)0x45)
#define FOC2 		         7
#define WGM20		         6
#define COM21		         5
#define COM20 		         4
#define WGM21 		         3
#define CS22 		         2
#define CS21 		         1
#define CS20		         0



#define TCNT2	             *((volatile u8*)0x44)
#define	OCR2	             *((volatile u8*)0x43)


#define TIMSK	             *((volatile u8*)0x59)
#define OCIE2		         7
#define TOIE2		         6



#define TIFR		         *((volatile u8*)0x58)
#define OCF2 		         7
#define TOV2		         6



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

#define TIMER2_OVF_vect		__vector_5

#endif /* MCAL_TIMER0_TIMER0_PRIV_H_ */
