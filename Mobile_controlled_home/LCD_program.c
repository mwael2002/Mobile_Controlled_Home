/*
 * LCD_program.c

 *
 *  Created on: Sep 11, 2021
 *      Author: mwael
 */
#include "STD_Types.h"
#include "bit_calc.h"
#include <avr/delay.h>
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_interface.h"

S8 current_address;
S8 right_top_limit;
S8 right_bottom_limit;
S8 left_top_limit;
S8 left_bottom_limit;


void LCD_init(void){
	DIO_set_port_direction(LCD_data_port,Port_8_pins_OUTPUT);
	DIO_set_pin_direction(LCD_control_port,LCD_Rs_pin,OUTPUT);
	DIO_set_pin_direction(LCD_control_port,LCD_Rw_pin,OUTPUT);
	DIO_set_pin_direction(LCD_control_port,LCD_E_pin,OUTPUT);
    _delay_ms(40);
    LCD_send_cmd(0b00111000);
    _delay_us(50);
    LCD_send_cmd(0b00001100);
    _delay_us(50);
    LCD_send_cmd(1);
    _delay_ms(2);

    current_address=0;
    right_top_limit=init_right_top_limit;
    right_bottom_limit=init_right_bottom_limit;
    left_top_limit=init_left_top_limit;
    left_bottom_limit=init_left_bottom_limit;

}
void LCD_clear(void){
	LCD_send_cmd(1);
}

void LCD_move_curser_right(void){
    if((current_address!=39)&&(current_address!=103)){
	if((current_address!=right_top_limit)&&(current_address!=right_bottom_limit)){
		LCD_send_cmd(0b00010100);
		current_address++;
	}
	else if((current_address==right_top_limit)||(current_address==right_bottom_limit)){
			shift_display_left();
		}

}
}
void LCD_move_curser_left(void){
    if((current_address!=0)&&(current_address!=64)){
	if((current_address!=left_top_limit)&&(current_address!=left_bottom_limit)){
		LCD_send_cmd(0b00010000);
		current_address--;
	}
	else if((current_address==left_top_limit)||(current_address==left_bottom_limit)){
            shift_display_right();
		}

}
}
void LCD_move_curser_bottom(void){
	if((current_address+40)>103){
		return;
	}
	current_address=current_address+64;
	LCD_send_cmd(current_address+128);
}
void LCD_move_curser_top(void){
	if((current_address-40)<0){
		return;
	}
	current_address=current_address-64;
	LCD_send_cmd(current_address+128);
}


void shift_display_left(void){
	LCD_send_cmd(0b00011000);
	right_top_limit++;
	right_bottom_limit++;
	left_top_limit++;
	left_bottom_limit++;
}
void shift_display_right(void){
	LCD_send_cmd(0b00011100);
	right_top_limit--;
	right_bottom_limit--;
	left_top_limit--;
	left_bottom_limit--;
}



void shift_entire_display_right_initial_pos(void){
for(U8 counter=0;counter<24;counter++){
	LCD_send_cmd(0b00011100);
}
current_address=init_left_bottom_limit;

right_top_limit=init_right_top_limit;
right_bottom_limit=init_right_bottom_limit;
left_top_limit=init_left_top_limit;
left_bottom_limit=init_left_bottom_limit;
}



void LCD_write_char(U8 Data){
	DIO_set_pin_value(LCD_control_port,LCD_Rs_pin,HIGH);
		LCD_send_data(Data);
}

void LCD_write_string(const char* str){
		    U8 counter=0;
			while(str[counter]!='\0'){
				if(current_address==39){
					LCD_send_cmd(128+current_address);
					LCD_write_char(str[counter]);

					shift_entire_display_right_initial_pos();

					counter++;
					continue;
				}
				if((current_address==right_top_limit)||(current_address==right_bottom_limit)){
				  shift_display_left();
				  continue;
				}
				LCD_write_char(str[counter]);
				counter++; current_address++;
			}
}
U8 LCD_write_string_pos(const char* str,U8 y_pos,U8 x_pos){
		U8 error_state=OK;
		if((y_pos<2)&&(x_pos<16)){
			current_address=(x_pos+(right_top_limit-15)+(y_pos*64));
			LCD_send_cmd(128+current_address);
			LCD_write_string(str);

		}
	else{
		error_state=NOK;
	}
	return error_state;
}

void LCD_write_no(U32 num){
	U8 rem,counter=0;
		char str[20];
		char str_2[20];
		if(num==0){
			str_2[counter]='0';
			counter++;
			str_2[1]='\0';
		}
		else{
			while(num!=0){
		rem=num%10;
		str[counter]=rem+'0';
		counter++;
		num=num/10;
		}
			str[counter]='\0';
			U8 j=0;
			for(S8 i=(counter-1);i>=0;i--){
				str_2[j]=str[i];
				j++;
			}
			str_2[j]='\0';
		}
		LCD_write_string(str_2);
}
void LCD_write_no_pos(U32 num,U8 y_pos, U8 x_pos){
	U8 rem,counter=0;
	char str[20];
	char str_2[20];
	if(num==0){
		str_2[counter]='0';
		counter++;
		str_2[1]='\0';
	}
	else{
		while(num!=0){
	rem=num%10;
	str[counter]=rem+'0';
	counter++;
	num=num/10;
	}
		str[counter]='\0';
		U8 j=0;
		for(S8 i=(counter-1);i>=0;i--){
			str_2[j]=str[i];
			j++;
		}
		str_2[j]='\0';
	}
	LCD_write_string_pos(str_2,y_pos,x_pos);
}




static void LCD_send_data(U8 data){
	DIO_set_pin_value(LCD_control_port,LCD_Rw_pin,LOW);
	DIO_set_port_value(LCD_data_port,data);
	DIO_set_pin_value(LCD_control_port,LCD_E_pin,HIGH);
	_delay_ms(1);
	DIO_set_pin_value(LCD_control_port,LCD_E_pin,LOW);
}
static void LCD_send_cmd(U8 cmd){
	DIO_set_pin_value(LCD_control_port,LCD_Rs_pin,LOW);
	LCD_send_data(cmd);
}
