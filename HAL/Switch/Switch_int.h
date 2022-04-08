/*
 * Switch_int.h
 *
 *  Created on: Mar 10, 2022
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_

ES_t Switch_enuInit(SW_t * Copy_pAstrSwitchConfig);

ES_t Switch_enuGetPressed(SW_t * Copy_pstrSwitchInfo , u8 * Copy_pu8Value);

#endif /* SWITCH_INT_H_ */
