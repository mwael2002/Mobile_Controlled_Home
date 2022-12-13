/*
 * USART_private.h
 *
 *  Created on: Sep 18, 2022
 *      Author: mwael
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define CHARSIZE_8_BIT  3
#define CHARSIZE_9_BIT  7
#define CHARSIZE_MASK  0b11111001

#define ASYNCHRONOUS   0
#define SYNCHRONOUS    1

#define PARITY_DISABLED 0
#define EVEN_PARITY     2
#define ODD_PARITY      3
#define PARITY_MASK     0b11001111

#define STOP_BIT_1      0
#define STOP_BIT_2      1

#define USART_TIME_OUT     10000UL
#define BAUD_RATE_MASK   0

#define USART_ENABLE  1
#define USART_DISABLE 0

#endif /* USART_PRIVATE_H_ */
