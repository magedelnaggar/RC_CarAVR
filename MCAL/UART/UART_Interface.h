/*
 * UART_Interface.h
 *
 * Created: 4/1/2022 8:10:01 PM
 *  Author: Abdelhai
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_






void UART_Init(void);
void UART_Send(u8 data);
u8 UART_Receive(void);



#endif /* UART_INTERFACE_H_ */
