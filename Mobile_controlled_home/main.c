/*
 * main.c
 *
 *  Created on: Feb 19, 2022
 *      Author: mwael
 */

#include <string.h>
#include <util/delay.h>
#include "bit_calc.h"
#include "STD_Types.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"
#include "EEPROM_interface.h"
#include "LED_interface.h"
#include "Buzzer_interface.h"

#define SIGN_IN                            1
#define NORMAL                             2
#define INCORRECT_PASSWORD_OR_USERNAME     4
#define INCORRECT_PASSWORD                 5


typedef struct{
 	char name[20];
	char pas[20];
}name_pas_S;

U8 adrs[10]={0,25,50,75,100,125,150,175,200,225};  //addresses of usernames&passwords in EEPROM

name_pas_S name_pas_check;

char receive[20];                //variable for recieving data except username & password for sign in through UART


LED Light_System[8];

U8 func=1;                       //variable for modes of operating

U8 user_id;                      //variable for storing user_id which is order of users in EEPROM
U8 pas_flag=0;
U8 incorrect_pas=0;              //variable that changes it's value in case of incorrect password

U8 door_lock=0;                  //variable that changes it's value in case of correct password to open the door lock


void system_init(void);          // function that initialize the system
void sign_in(void);              //function that responsible for signing in of user
void do_nothing(void);
void open_close_lock(void);      //function to open and close door lock
void switch_led(void);           //function for turning on/off leds
void change_username_pas(void);  //function for changing username and password
void log_out(void);              //function for logging out of the user
void alarm (void);               //function for turning on alarm in case of entering username or password 3 times incorrect


void main(void){
    system_init();

    EEPROM_init();

    USART_init();
    Global_Int_En_Dis(Global_Int_Enable);

	while(1){
    sign_in();
    open_close_lock();
    switch_led();
    change_username_pas();
    log_out();
	}
}


void system_init(void){
	DIO_set_pin_direction(Group_D,DIO_Pin_0,INPUT);
	DIO_set_pin_direction(Group_D,DIO_Pin_1,OUTPUT);

	DIO_set_pin_direction(Group_D,DIO_Pin_7,OUTPUT);
	DIO_set_pin_value(Group_D,DIO_Pin_7,LOW);

	for(U8 led_counter=0;led_counter<8;led_counter++){
		Light_System[led_counter].LED_Port=Group_A;
		Light_System[led_counter].LED_Pin=led_counter;
		Light_System[led_counter].LED_Type=LED_Source;
		LED_init(&Light_System[led_counter]);
		LED_OFF(&Light_System[led_counter]);
	}

}

void sign_in(void){
	if(func==SIGN_IN){
		name_pas_S read_name_pas;
        name_pas_S name_pas_check;

        name_pas_check.name[0]='\0';
        name_pas_check.pas[0]='\0';

		static U8 flag_incorrect_pas=0;


	    USART_receive_string_asynch(name_pas_check.name,do_nothing);
		while(name_pas_check.name[0]=='\0');

		_delay_ms(25);

        USART_receive_string_asynch(name_pas_check.pas,do_nothing);
		while(name_pas_check.pas[0]=='\0');

		_delay_ms(25);

		for(S8 i=9;i>=0;i--){
			EEPROM_read_string(read_name_pas.name,adrs[i],0);
			EEPROM_read_string(read_name_pas.pas,adrs[i],3);

			if((strcmp(name_pas_check.name,read_name_pas.name)==0)&&(strcmp(name_pas_check.pas,read_name_pas.pas)==0)){
			  user_id=i;
			  flag_incorrect_pas=0;
			  door_lock=1;

			  USART_send_string_synch("Welcome");

			  name_pas_check.name[0]='\0';
              name_pas_check.pas[0]='\0';

              func=NORMAL;

			  USART_receive_string_asynch(receive,do_nothing);
              return;
			}
		   }

		       USART_send_string_synch("Incorrect username");

			   flag_incorrect_pas++;

			   name_pas_check.name[0]='\0';
               name_pas_check.pas[0]='\0';

		   if(flag_incorrect_pas==3){
			func=INCORRECT_PASSWORD_OR_USERNAME;
			alarm();
		}
	}
		}






void open_close_lock(void){
	if(func==NORMAL){
		if((strcmp(receive,"3")==0)||(door_lock==1)){
			DIO_set_pin_value(Group_D,DIO_Pin_7,HIGH);
			door_lock=0;
			USART_receive_string_asynch(receive,do_nothing);
		}
		else if(strcmp(receive,"4")==0){
			DIO_set_pin_value(Group_D,DIO_Pin_7,LOW);
			USART_receive_string_asynch(receive,do_nothing);
				}
	}
}

void switch_led(void){
	if(func==NORMAL){
		for(U8 i=1;i<9;i++){
			if((receive[0]=='O')&&(receive[1]=='N')&&((receive[2])==(i+48))){
				LED_ON(&Light_System[i-1]);
				USART_receive_string_asynch(receive,do_nothing);
			}
			else if((receive[0]=='O')&&(receive[1]=='F')&&(receive[2]=='F')&&((receive[3])==(i+48))){
				LED_OFF(&Light_System[i-1]);
				USART_receive_string_asynch(receive,do_nothing);
			}
			}
		}
}


void change_username_pas(void){
	if(func==NORMAL){
		char pas_check[22];
        char pas_read[20];

      EEPROM_read_string(pas_read,adrs[user_id],3);

      if((receive[0]=='A')&&(pas_flag==0)){
    	  _delay_ms(25);
    	  U8 j=0;
    	  do{
    	       pas_check[j]=receive[j+1];
    	       j++;
    	      }while(pas_check[j-1]!='\0');

    	  if(strcmp(pas_read,pas_check)==0){
          incorrect_pas=0;
    	  pas_flag=1;
    	  USART_send_string_synch("Password is correct");
    	  receive[0]='\0';
    	  USART_receive_string_asynch(receive,do_nothing);
    	  return;
    	  }

    	  USART_send_string_synch("Incorrect password");
          incorrect_pas++;
          receive[0]='\0';
          USART_receive_string_asynch(receive,do_nothing);

          if(incorrect_pas==3){
        	  system_init();
        	  _delay_ms(25);
        	  func=INCORRECT_PASSWORD;
        	  alarm();
          }

      }

      if(pas_flag==1){
    	  if(receive[0]=='B'){
    		  _delay_ms(25);
    		  U8 i=0;
    		 do{
    			 receive[i]=receive[i+1];
    			 i++;
    		 }while(receive[i-1]!='\0');
    		 EEPROM_write_string(receive,adrs[user_id],0);
    		 USART_send_string_synch("Username has changed");
    		 pas_flag=0;
    		 USART_receive_string_asynch(receive,do_nothing);
    	  }

    	  else if(receive[0]=='C'){
    	      _delay_ms(25);
    	      U8 i=0;
    	      do{
    	    	 receive[i]=receive[i+1];
    	    	 i++;
    	       }while(receive[i-1]!='\0');

    	      EEPROM_write_string(receive,adrs[user_id],3);
    	      USART_send_string_synch("Password has changed");
    	  	  pas_flag=0;
    	  	  USART_receive_string_asynch(receive,do_nothing);
    	  }
      }

 }
}


void log_out(void){
	if(func==NORMAL){
	if(strcmp(receive,"11")==0){
		pas_flag=0;
		incorrect_pas=0;
		system_init();
		USART_send_string_synch("Logged Out");
	    receive[0]='\0';
		func=SIGN_IN;
	}
}
}

void alarm(void){
	Buzzer_init();
	Buzzer_On();
    if(func==INCORRECT_PASSWORD_OR_USERNAME){
    	USART_send_string_synch("User or Password is incorrect for 3 times the system will close");
    }
    else if(func==INCORRECT_PASSWORD){
    	USART_send_string_synch("Password is incorrect for 3 times the system will close");
    }
}



void do_nothing(void){

}
