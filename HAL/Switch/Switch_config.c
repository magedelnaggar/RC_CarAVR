/*
 * Switch_config.c
 *
 *  Created on: Mar 10, 2022
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "Switch_config.h"
#include "Switch_priv.h"

u8 Switch_u8SwitchNum = SW_NUM;

SW_t Switch_AstrSwitchConfig [ SW_NUM ]=
{
		{DIO_u8GROUP_D , DIO_u8PIN2 , DIO_u8PULL_UP},
		//{DIO_u8GROUP_D , DIO_u8PIN3 , DIO_u8PULL_UP},
		//{DIO_u8GROUP_D , DIO_u8PIN4 , DIO_u8PULL_UP},
		{DIO_u8GROUP_D , DIO_u8PIN5 , DIO_u8PULL_UP}
};

