/*
 * USART_config.h
 *
 *  Created on: Sep 18, 2022
 *      Author: mwael
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/*options: 1-CHARSIZE_8_BIT
 *         2-CHARSIZE_9_BIT */
#define CHARSIZE    CHARSIZE_8_BIT


/*OPTIONS: 1-ASYNCHRONOUS
 *         2-SYNCHRONOUS */
#define USART_MODE  ASYNCHRONOUS


/*OPTIONS: 1-PARITY_DISABLED
 *         2-EVEN_PARITY
 *         3-ODD_PARITY */
#define PARITY_MODE  PARITY_DISABLED


/*options: 1-STOP_BIT_1
 *         2-STOP_BIT_2 */
#define STOP_BIT    STOP_BIT_1


#define FOSC        8000000UL
#define BAUD_RATE   9600UL


#define USART_USE_DOUBLE_SPEED       0


/*options: 1- USART_ENABLE
 *         2- USARTISABLE */
#define USART_RECEIVER_STATE              USART_ENABLE
#define USART_TRANSMITTER_STATE           USART_ENABLE

#endif /* USART_CONFIG_H_ */
