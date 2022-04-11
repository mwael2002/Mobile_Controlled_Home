/*
 * UART_interface.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mwael
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define enable 1
#define disable 0

void UART_init(void);
void Enable_TX(void);

void UART_send_char(U8 data);
U8 UART_recieve_char(void);
void UART_send_string(char* str2);
char* UART_recieve_string(void);

void __vector_13(void) __attribute__((signal));
void __vector_14(void) __attribute__((signal));
//void __vector_15(void) __attribute__((signal));
char send_string(void);

void callback_UART(void(*ptr)(void));
void ptr_mailbox_call_back_UART(void (*ptr) (void));
void char_call_back_UART(char (*ptr) (void));


void UART_post_string_buffer(void);
char* UART_recieve_string_buffer(void);

void post_mailbox(void);
char* recieve_mailbox(void);
void delete_mailbox(void);
#endif /* UART_INTERFACE_H_ */
