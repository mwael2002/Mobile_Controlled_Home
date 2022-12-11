/*
 * main.c
 *
 *  Created on: Feb 19, 2022
 *      Author: mwael
 */
#include"string.h"
#include"util/delay.h"
#include"bit_calc.h"
#include"STD.Types.h"
#include"DIO_interface.h"
#include "EEPROm_interface.h"
#include"UART_interface.h"
//structure for name&user password
typedef struct{
 	char *name;
	char *pas;
}name_pas;

U8 adrs[10]={0,25,50,75,100,125,150,175,200,225};  //addresses of usernames&passwords in EEPROM

char *recieve=(void*)0;          //variable for recieving data through UART
char *string=(void*)0;           //variable for senting data through UART

U8 func=1;                       //variable for modes of operating

U8 user_id;                      //variable for storing user_id which is order of users in EEPROM
U8 pas_flag=0;
U8 incorrect_pas=0;              //variable that changes it's value in case of incorrect password

U8 door_lock=0;                  //variable that changes it's value in case of correct password to open the door lock

void system_init(void);          // function that initialize the system
void sign_in(void);              //function that responsible for signing in of user
void open_close_lock(void);      //function to open and close door lock
void switch_led(void);           //function for turning on/off leds
void change_username_pas(void);  //function for changing username and password
void log_out(void);              //function for logging out of the user
void alarm (void);               //function for turning on alarm in case of entering username or password 3 times incorrect

void main(void){
    system_init();
    EEpromInit();

    callback_UART(UART_post_string_buffer);
    ptr_mailbox_call_back_UART(post_mailbox);
    char_call_back_UART(send_string);
    UART_init();
    Enable_Disable_data_RX_interrupt(enable);
    Enable_Disable_RX(enable);


	while(1){
    sign_in();
    open_close_lock();
    switch_led();
    change_username_pas();
    log_out();
    recieve=recieve_mailbox();
	}
}


void system_init(void){
	DIO_set_pin_direction(Group_D,DIO_Pin_D0,INPUT);
	DIO_set_pin_direction(Group_D,DIO_Pin_D1,OUTPUT);
	DIO_set_pin_direction(Group_D,DIO_Pin_D7,OUTPUT);
	DIO_set_pin_value(Group_D,DIO_Pin_D7,LOW);
	DIO_set_port_direction(Group_A,DIO_Max_Port_direction);
	DIO_set_port_value(Group_A,LOW);

	  Enable_Disable_data_register_empty_interrupt(enable);
	  Enable_Disable_TX(enable);
}

void sign_in(void){
	if(func==1){
		name_pas name_pas_check;
		name_pas read_name_pas;
		static U8 flag_incorrect_pas=0;
		char* flag_name_pas=(void*)0;

		flag_name_pas=UART_recieve_string_buffer();
		if(strcmp(flag_name_pas,"1")==0){
		name_pas_check.name=UART_recieve_string_buffer();
		name_pas_check.pas=UART_recieve_string_buffer();
		for(S8 i=9;i>=0;i--){
			read_name_pas.name=EEprom_read_string(adrs[i],0);
			read_name_pas.pas=EEprom_read_string(adrs[i],3);
			if((strcmp(name_pas_check.name,read_name_pas.name)==0)&&(strcmp(name_pas_check.pas,read_name_pas.pas)==0)){
			  user_id=i;
			  string=" Welcome ";


			  func=2;
			  flag_incorrect_pas=0;
			  door_lock=1;
              return;
			}
		   }
		}
		   if(strcmp(flag_name_pas,"1")==0){
			   string=" Incorrect username or password ";

			   flag_incorrect_pas++;
				flag_name_pas=0;
			}

		   if(flag_incorrect_pas==3){
			func=4;
			alarm();
		}
	}
		}


void open_close_lock(void){
	if(func==2){
		if((strcmp(recieve,"3")==0)||(door_lock==1)){
			DIO_set_pin_value(Group_D,DIO_Pin_D7,HIGH);
			door_lock=0;
		}
		else if(strcmp(recieve,"4")==0){
			DIO_set_pin_value(Group_D,DIO_Pin_D7,LOW);
				}
	}
}
void switch_led(void){
	if(func==2){
		for(U8 i=1;i<9;i++){
			if((recieve[0]=='O')&&(recieve[1]=='N')&&((recieve[2])==(i+48))){
				DIO_set_pin_value(Group_A,i-1,HIGH);
			}
			else if((recieve[0]=='O')&&(recieve[1]=='F')&&(recieve[2]=='F')&&((recieve[3])==(i+48))){
				DIO_set_pin_value(Group_A,i-1,LOW);
			}
			}
		}
}


void change_username_pas(void){
	if(func==2){
		char *pas_check;

      EEprom_read_string(0,0);
      char*pas_read=EEprom_read_string(adrs[user_id],3);

      if((recieve[0]=='A')&&(pas_flag==0)){
    	  _delay_ms(25);
    	  U8 j=0;
    	  do{
    	       pas_check[j]=recieve[j+1];
    	       j++;
    	      }while(pas_check[j-1]!='\0');

    	  if(strcmp(pas_read,pas_check)==0){
          incorrect_pas=0;
    	  pas_flag=1;
    	  string=" Password is correct ";
    	  delete_mailbox();
    	  return;
    	  }
    	  delete_mailbox();
          string=" Incorrect password ";
          incorrect_pas++;
          if(incorrect_pas==3){
        	  system_init();
        	  _delay_ms(25);
        	  func=5;
        	  alarm();
          }

      }
      if(pas_flag==1){
    	  if(recieve[0]=='B'){
    		  _delay_ms(25);
    		  U8 i=0;
    		 do{
    			 recieve[i]=recieve[i+1];
    			 i++;
    		 }while(recieve[i-1]!='\0');
    		 EEprom_write_string(recieve,adrs[user_id],0);
    		 string=" Username has changed ";
    		 delete_mailbox();
    		 pas_flag=0;
    	  }
    	  else if(recieve[0]=='C'){
    	    		  _delay_ms(25);
    	    		  U8 i=0;
    	    		 do{
    	    			 recieve[i]=recieve[i+1];
    	    			 i++;
    	    		 }while(recieve[i-1]!='\0');
    	    		 EEprom_write_string(recieve,adrs[user_id],3);
    	  	         string=" Password has changed ";
    	  	         delete_mailbox();
    	  	         pas_flag=0;
    	    	  }
      }
}
}


void log_out(void){
	if(func==2){
	if(strcmp(recieve,"11")==0){
		pas_flag=0;
		incorrect_pas=0;
		system_init();
		string=" Logged Out ";
		_delay_ms(10);
	    func=1;
	}
}
}

void alarm(void){
	DIO_set_pin_direction(Group_D,DIO_Pin_D3,OUTPUT);
	DIO_set_pin_value(Group_D,DIO_Pin_D3,HIGH);
    if(func==4){
    	string=" User or Password is incorrect for 3 times the system will close ";
    }
    else if(func==5){
    	string=" Password is incorrect for 3 times the system will close ";
    }
}

