/*
 * Switch_config.h
 *
 *  Created on: Mar 10, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef SWITCH_CONFIG_H_
#define SWITCH_CONFIG_H_

#define SW_NUM			2

typedef struct
{
	u8 Sw_Grp;
	u8 Sw_Pin;
	u8 Sw_State;
}SW_t;

#endif /* SWITCH_CONFIG_H_ */
