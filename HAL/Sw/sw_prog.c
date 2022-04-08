/*
 * sw_prog.c
 *
 *  Created on: Mar 10, 2022
 *      Author: Ahmed El-Gaafrawy
 */
//public lib
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

//lower
#include "../../MCAL/DIO/DIO_int.h"

//own
#include "sw_config.h"
#include "sw_priv.h"

ES_t Sw_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK , arr[2];

	arr[0]=DIO_enuSetPinDirection(SW_GROUP, SW_PIN, DIO_u8INPUT);
	arr[1]=DIO_enuSetPinValue(SW_GROUP, SW_PIN, SW_STATE);

	if (arr[0] == ES_OK && arr[1]==ES_OK)
		Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t Sw_enuGetPressed(u8 * Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pu8Value != NULL)
	{
		Local_enuErrorState = DIO_enuGetPinValue(SW_GROUP , SW_PIN, Copy_pu8Value);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

