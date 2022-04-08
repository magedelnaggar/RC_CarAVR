/*
 * HC_05_Prog.c
 *
 * Created: 4/1/2022 8:10:01 PM
 *  Author: Abdelhai
 */ 
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/UART/UART_Interface.h"


#include <avr/io.h>

#include "HC_05_Config.h"
#include "HC_05_Private.h"

void HC_05_Init(void)
{
	UART_Init();

}
u8 HC_05_Receive(void)
{
	static u8 data;
	data = UART_Receive();
	return data;
}
