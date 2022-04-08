/*
 * Switch_prog.c
 *
 *  Created on: Mar 10, 2022
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "Switch_config.h"
#include "Switch_priv.h"

extern u8 Switch_u8SwitchNum;

ES_t Switch_enuInit(SW_t * Copy_pAstrSwitchConfig)
{
	ES_t Local_enuErrorState = ES_NOK , arr[2], state = ES_OK;

	if (Copy_pAstrSwitchConfig != NULL)
	{
		u8 Local_u8Iter =0;
		for ( ; Local_u8Iter< Switch_u8SwitchNum ; Local_u8Iter++)
		{
			arr[0]=DIO_enuSetPinDirection(Copy_pAstrSwitchConfig[Local_u8Iter].Sw_Grp ,
					 (Copy_pAstrSwitchConfig + Local_u8Iter)->Sw_Pin,
					 DIO_u8INPUT);

			arr[1]=DIO_enuSetPinValue(Copy_pAstrSwitchConfig[Local_u8Iter].Sw_Grp,
					Copy_pAstrSwitchConfig[Local_u8Iter].Sw_Pin,
					Copy_pAstrSwitchConfig[Local_u8Iter].Sw_State);

			if (arr[0]!= ES_OK || arr[1]!= ES_OK)
			{
				state = ES_NOK;
				break;
			}
		}
		if (state == ES_OK)
			Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t Switch_enuGetPressed(SW_t * Copy_pstrSwitchInfo , u8 * Copy_pu8Value)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_pstrSwitchInfo != NULL &&
			Copy_pu8Value != NULL)
	{
		Local_enuErrorState = DIO_enuGetPinValue(Copy_pstrSwitchInfo -> Sw_Grp
				,Copy_pstrSwitchInfo->Sw_Pin ,
				Copy_pu8Value);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

