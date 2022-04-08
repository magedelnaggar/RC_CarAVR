/*
 * USconfig.h
 *
 *  Created on: Mar 31, 2022
 *      Author: abdel
 */

#ifndef HAL_ULTRASONIC_USCONFIG_H_
#define HAL_ULTRASONIC_USCONFIG_H_


#define TRIGGER_PIN		DIO_u8PIN0
#define TRIGGER_GR		DIO_u8GROUP_C

#define ECHO_PIN		DIO_u8PIN1
#define ECHO_GR			DIO_u8GROUP_C


#define CRYSTAL_FREQ		16
#define PRESCALING			1

#define TICK_TIME 			16



#endif /* HAL_ULTRASONIC_USCONFIG_H_ */
