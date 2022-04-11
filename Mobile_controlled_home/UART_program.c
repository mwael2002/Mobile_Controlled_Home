/*
 * UART_program.c
 *
 *  Created on: Oct 29, 2021
 *      Author: mwael
 */
#include"string.h"
#include"D:/C/STD.Types.h"
#include"D:/C/bit_calc.h"
#include"UART_private.h"
#include"UART_interface.h"

void (*ptr_UART) (void);
void (*ptr_mailbox)(void);
char (*char_ptr_UART) (void);

U8 flag=3;
U8 sign=0;
char buffer[3][23];
char mailbox[23];

extern U8 func;
extern char*string;

void UART_init(void){
	UBRRH=0b00000000;  //select UBRRH
	UBRRL=51;
	UCSRC=0b10000110;  //select UCSRC
	                   //Asynchronous
                       //No parity
	                   // 1 stop bit
	                   // 8 data bits
	UCSRB=0b10010000;
    set_bit(SREG,7);
}

void Enable_TX(void){
	set_bit(UCSRB,3);
	set_bit(UCSRB,5);
}


void UART_send_char(U8 data){
while (get_bit(UCSRA,5)==0);
UDR=data;
}
U8 UART_recieve_char(void){
while (get_bit(UCSRA,7)==0);
return UDR;
}
void UART_send_string(char *str){
	U8 i=0;
while(str[i]!='\0'){
	UART_send_char(str[i]);
	i++;
}
}
char* UART_recieve_string(void){
char*str;
U8 i=0;
while(str[i-1]!='\n'){
	str[i]=UART_recieve_char();
	i++;
}
str[i-1]='\0';
return str;
}


void callback_UART(void(*ptr)(void)){
	ptr_UART=ptr;
}

void char_call_back_UART(char (*ptr) (void)){
	char_ptr_UART=ptr;
}
void __vector_14(void){
		UDR=char_ptr_UART();
}


void ptr_mailbox_call_back_UART(void (*ptr) (void)){
	ptr_mailbox=ptr;
}
void __vector_13(void){
	if(func==1){
	ptr_UART();
	}
	else if(func==2){
	ptr_mailbox();
	}
}


char send_string(void){
       	static U8 i=0;
       	i++;
       	if(string[i-1]=='\0'){
       		i=0;
       		return '\0';
       	}
       	else{
       	return string[i-1];
       	}
       	}


void UART_post_string_buffer(void){
		static U8 buffer_no=0;
	    static U8 string_length=0;
	    delete_mailbox();
	if(flag!=0){
            buffer[buffer_no][string_length]=UDR;
			string_length++;
	if((buffer[buffer_no][string_length-1]=='0')&&(buffer[buffer_no][string_length-2]=='/')){
		buffer[buffer_no][string_length-2]='\0';
		string_length=0;
		if((strcmp(buffer[0],"1")==0)||(sign==1)){
		buffer_no++;
	    flag--;
	    sign=1;
	}
    if(buffer_no==3){
    	buffer_no=0;
    }
}
}
}
char* UART_recieve_string_buffer(void){
	static U8 buffer_no=0;
	if(buffer_no==3){
		buffer_no=0;
	}
	if(flag==0){
		buffer_no++;
        if(buffer_no==3){
        	flag=3;
        	sign=0;
        }
		return buffer[buffer_no-1];
	}
	else{
	return "\0";
	}
	}


void post_mailbox(void){
	static U8 string_length=0;
		mailbox[string_length]=UDR;
		string_length++;
		if((mailbox[string_length-1]=='0')&&(mailbox[string_length-2]=='/')){
			mailbox[string_length-2]='\0';
	        string_length=0;
	}
}
char* recieve_mailbox(void){
        return mailbox;
}
void delete_mailbox(void){
	memset(mailbox,0,sizeof(mailbox));
}
