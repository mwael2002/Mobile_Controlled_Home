/*
 * USART_interface.h
 *
 *  Created on: Sep 18, 2022
 *      Author: mwael
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_init(void);
U8 USART_send_char(U8 data);
U8 USART_receive_char(U8* Copy_Data);

U8 USART_send_string_synch(const char* copy_string);
U8 USART_receive_string_synch(char* copy_string);

U8 USART_send_string_asynch(const char* copy_string,void (*copy_notify_func)(void));
U8 USART_receive_string_asynch(char* copy_string,void (*copy_notify_func)(void));

void USART_send_no(U32 no);
U32 USART_receive_no(void);

void USART_change_USART_RX_string(char* copy_string);

#endif /* USART_INTERFACE_H_ */
