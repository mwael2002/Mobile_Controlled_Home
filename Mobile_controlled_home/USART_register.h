/*
 * USART_register.h
 *
 *  Created on: Sep 18, 2022
 *      Author: mwael
 */

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UDR           *((volatile U8*)0x2C)

#define UCSRA         *((volatile U8*)0x2B)
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

#define UCSRB         *((volatile U8*)0x2A)
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

#define UCSRC         *((volatile U8*)0x40)
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#define UBRRH         *((volatile U8*)0x40)
#define URSEL   7
#define UBRR11  3
#define UBRR10  2
#define UBRR9   1
#define UBRR8   0

#define UBRRL         *((volatile U8*)0x29)
#define UBRR7   7
#define UBRR6   6
#define UBRR5   5
#define UBRR4   4
#define UBRR3   3
#define UBRR2   2
#define UBRR1   1
#define UBRR0   0

#endif /* USART_REGISTER_H_ */
