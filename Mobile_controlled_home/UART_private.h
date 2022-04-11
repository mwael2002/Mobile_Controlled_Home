/*
 * UART_private.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mwael
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR *((volatile U8*)0x2C)
#define UCSRA *((volatile U8*)0x2B)
#define UCSRB *((volatile U8*)0x2A)
#define UCSRC *((volatile U8*)0x40)
#define UBRRH *((volatile U8*)0x40)
#define UBRRL *((volatile U8*)0x29)
#define SREG *((volatile U8*)0X5F)
#endif /* UART_PRIVATE_H_ */
