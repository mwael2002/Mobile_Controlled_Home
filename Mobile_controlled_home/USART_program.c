/*
 * USART_program.c
 *
 *  Created on: Sep 18, 2022
 *      Author: mwael
 */

#include "STD_Types.h"
#include "bit_calc.h"
#include "USART_register.h"
#include "USART_config.h"
#include "USART_private.h"
#include "USART_interface.h"


static void(*USART_Receive_Notification_Func)(void)=NULL;
static void(*USART_Send_Notification_Func)(void)=NULL;
static char* USART_Receive_Data=NULL;
static const char* USART_Send_Data=NULL;



void USART_init(void){
   U8 UCSRC_value=0;
   U32 Baud_value=0;

	//choose the UCSRC_value register
	set_bit(UCSRC_value,URSEL);

	//character size
	UCSRC_value &= CHARSIZE_MASK;

#if CHARSIZE == CHARSIZE_8_BIT
        clear_bit(UCSRB,UCSZ2);
	UCSRC_value |= (CHARSIZE<<1);

#elif CHARSIZE == CHARSIZE_9_BIT
        set_bit(UCSRB,UCSZ2);
        UCSRC_value |= (CHARSIZE<<1);
#endif



#if USART_MODE == ASYNCHRONOUS
	clear_bit(UCSRC_value,UMSEL);
#elif USART_MODE == SYNCHRONOUS
	set_bit(UCSRC_value,UMSEL);
#endif

//parity mode
UCSRC_value &= PARITY_MASK;
UCSRC_value |= PARITY_MODE;



#if STOP_BIT == STOP_BIT_1
	clear_bit(UCSRC_value,USBS);
#elif  STOP_BIT == STOP_BIT_2
	set_bit(UCSRC_value,USBS);
#endif

UCSRC=UCSRC_value;

        UBRRH =0;

#if USART_USE_DOUBLE_SPEED==1
         set_bit(UCSRA,1);
       //Baud Rate Setting
	Baud_value=(FOSC/(8* BAUD_RATE))-1;
     //   LCD_write_no_pos(Baud_value,0,1);
         UBRRL=(U8)Baud_value;
	UBRRH=(Baud_value>>8);
#else
	Baud_value=(FOSC/(16* BAUD_RATE))-1;
     //   LCD_write_no_pos(Baud_value,0,1);
         UBRRL=(U8)Baud_value;
	UBRRH=(Baud_value>>8);
#endif

	assign_bit(UCSRB,TXEN,USART_TRANSMITTER_STATE);

	assign_bit(UCSRB,RXEN,USART_RECEIVER_STATE);


}

U8 USART_send_char(U8 data){

	U32 counter=0;
	U8  Error_State=OK;
	//wait until the transmit buffer is empty  and ready or  the timeout is reached
	while((get_bit(UCSRA,UDRE)==0)&&(counter<USART_TIME_OUT)){
		counter++;
	}

	if(counter==USART_TIME_OUT){
		Error_State=TIMEOUT_STATE;
        }
	else{
	     //send the data
	     UDR=data;
	}
	return Error_State;
}

U8 USART_receive_char(U8* Copy_Data){

	U32 counter=0;
    U8 Error_State=OK;

	//wait until receive complete event happens
	while((get_bit(UCSRA,RXC)==0)&&(counter<USART_TIME_OUT)){
	counter++;
	}

	if(counter==USART_TIME_OUT){
		Error_State=TIMEOUT_STATE;
	}
		else{
			*Copy_Data=UDR;
		}
	return Error_State;
}



U8 USART_send_string_synch(const char* copy_string){

        U8 error_state=OK;
	    U8 counter=0;

   if(copy_string != NULL){
   while(copy_string[counter]!='\0'){
	USART_send_char(copy_string[counter]);
	counter++;
}

USART_send_char('\0');
}
	else {
	   error_state = NULL_POINTER;
	}
	   return error_state;
   }

U8 USART_receive_string_synch(char* copy_string){

	U8 error_state=OK;
	U8 counter=0;

	if(copy_string != NULL){

		while(1){
			USART_receive_char(&copy_string[counter]);
		   if(copy_string[counter]=='#'){
			   copy_string[counter]='\0';
			break;
			   }
		         counter++;
		}
	}
	else {
	   error_state = NULL_POINTER;
	}
	   return error_state;
}


U8 USART_send_string_asynch(const char* copy_string,void (*copy_notify_func)(void)){

	U8 error_state=OK;
	if((copy_string != NULL)&& (copy_notify_func != NULL)){
		USART_Send_Notification_Func=copy_notify_func;
		USART_Send_Data=copy_string;
		set_bit(UCSRB,UDRIE);
	}
	else{
	   error_state=NULL_POINTER;
	}
	   return error_state;
}




U8 USART_receive_string_asynch(char* copy_string,void (*copy_notify_func)(void)){

	U8 error_state=OK;
	if((copy_string != NULL)&&(copy_notify_func != NULL)){
		USART_Receive_Notification_Func=copy_notify_func;
		USART_Receive_Data=copy_string;
		set_bit(UCSRB,RXCIE);
	}

	else {
	   error_state=NULL_POINTER;
	}
	return error_state;
}

void USART_send_no(U32 no){
   	U8 rem,arr_index=0;
		 char str[15];
		 char str_2[15];
		
                 if(no==0){
			str_2[arr_index]='0';
			arr_index++;
			str_2[1]='\0';
		}
		else{
			while(no!=0){
		rem=no%10;
		str[arr_index]=rem+'0';
		arr_index++;
		no=no/10;
		}
			str[arr_index]='\0';
			U8 j=0;
		S8 i;	
		for(i=(arr_index-1);i>=0;i--){
				str_2[j]=str[i];
				j++;
			}
			str_2[j]='\0';
		}
		USART_send_string_synch(str_2);
}

U32 USART_receive_no(void){
   
char str_no[20];
USART_receive_string_synch(str_no);

 U32 no=0;
 U8 i=0;
   
 while(str_no[i]!='\0'){
 no= ((no*10) + (str_no[i]-48));
   i++;
    }
    return no;
  }



void __vector_14(void)    __attribute__((signal));
void __vector_14(void){

	static U8 counter=0;
	if((USART_Send_Notification_Func!= NULL)&& (USART_Send_Data != NULL)){

			UDR=USART_Send_Data[counter];
			counter++;

		if(USART_Send_Data[counter-1] == '\0'){
			clear_bit(UCSRB,UDRIE);
			counter=0;
			USART_Send_Notification_Func();
		}
	}
}

// USR: USART, Rx Complete Interrupt
void __vector_13(void)    __attribute__((signal));
void __vector_13(void){

	static U8 counter=0;
	if((USART_Receive_Notification_Func != NULL)&&(USART_Receive_Data != NULL)){
            USART_Receive_Data[counter]=UDR;
	        counter++;

		if (USART_Receive_Data[counter-1]=='#'){
			USART_Receive_Data[counter-1]='\0';
			clear_bit(UCSRB,RXCIE);
			counter=0;
			USART_Receive_Notification_Func();
		}

	}
}


