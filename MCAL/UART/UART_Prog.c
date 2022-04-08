/*
 * UART_Prog.c
 *
 * Created: 4/1/2022 8:10:01 PM
 *  Author: Abdelhai
 */ 
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"
#include "../../LIB/BIT_MATH.h"

#include "../DIO/DIO_int.h"


#include "UART_Config.h"
#include "UART_Private.h"
//#include "../Interrupt.h"
#include <util/delay.h>

void UART_Init(void)
{
	//to select PD1 (Tx) ->OUTPUT
	DIO_enuSetPinDirection(TX_GP,TX_pin,DIO_u8OUTPUT);
	//to select PD0 (Rx) ->INPUT
	DIO_enuSetPinDirection(RX_GP,RX_pin,DIO_u8INPUT);
	DIO_enuSetPinValue(RX_GP,RX_pin,DIO_u8PULL_UP);

	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
	// to select character size -> 8bits
	UCSRC = 0b10000110;

	CLR_BIT(UCSRB,2);
	// to select 9600 baud rate

	 /*1-bit stop*/
	 CLR_BIT(UCSRB,2);

	 // to select 9600 baud rate
	UBRRL = 103;
}
void UART_Send(u8 data)
{
	//while((GET_BIT(UCSRA,5)) == 0);
	UDR = data;
	//check transmitter flag
	while(GET_BIT(UCSRA,6)==0);
}
u8 UART_Receive(void)
{

u8 i=0;
	//check reciever flag
	while(GET_BIT(UCSRA,7)==0 && i<20)
	{
			_delay_ms(60);
			i++;
	}
	if(i==20)
	{
		//return '0';
	}
	else
	{
		return UDR;
	}

}
