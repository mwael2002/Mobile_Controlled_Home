/*
 * DIO_program.c
 *
 *  Created on: Sep 10, 2021
 *      Author: mwael
 */
#include"D:/C/bit_calc.h"
#include"D:/C/STD.Types.h"
#include"DIO_private.h"
#include"DIO_interface.h"
U8 DIO_set_pin_direction(U8 port_no,U8 pin_no,U8 pin_direction){
	U8 error_state=0;
	if(port_no >= DIO_Max_Port_no){
		error_state=1;
	}
	else if(port_no >= DIO_Max_Pin_no){
			error_state=1;
		}
	else if((pin_direction!=0)&&(pin_direction!=1)){
		error_state=1;
	}
	else{
		switch(port_no){
		case Group_A :
            assign_bit(DIO_U8_DDRA,pin_no,pin_direction) ;
			break;

		case Group_B :
		            assign_bit(DIO_U8_DDRB,pin_no,pin_direction) ;
					break;

        case Group_C :
            assign_bit(DIO_U8_DDRC,pin_no,pin_direction) ;
			break;

        case Group_D :
            assign_bit(DIO_U8_DDRD,pin_no,pin_direction) ;
			break;
		}
	}
	return error_state;
}

U8 DIO_set_pin_value(U8 port_no,U8 pin_no,U8 pin_value){
	U8 error_state=0;
	if(port_no >= DIO_Max_Port_no){
		error_state=1;
	}
	else if(port_no >= DIO_Max_Pin_no){
			error_state=1;
		}
	else if((pin_value!=0)&&(pin_value!=1)){
		error_state=1;
	}
	else{
		switch(port_no){
		case Group_A :
            assign_bit(DIO_U8_PORTA,pin_no,pin_value) ;
			break;

		case Group_B :
		            assign_bit(DIO_U8_PORTB,pin_no,pin_value) ;
					break;

        case Group_C :
            assign_bit(DIO_U8_PORTC,pin_no,pin_value) ;
			break;

        case Group_D :
            assign_bit(DIO_U8_PORTD,pin_no,pin_value) ;
			break;
		}
	}
	return error_state;
}



U8 DIO_set_port_direction(U8 port_no,U8 port_direction){
	U8 error_state=0;
	if(port_no >= DIO_Max_Port_no){
		error_state=1;
	}
	else if(port_direction>DIO_Max_Port_direction){
		error_state=1;
	}
	else{
		switch(port_no){
				case Group_A :
					DIO_U8_DDRA=port_direction ;
					break;
				case Group_B :
					DIO_U8_DDRB=port_direction;
					break;
				case Group_C :
					DIO_U8_DDRC=port_direction;
					break;
				case Group_D :
					DIO_U8_DDRD=port_direction;
					break;

				}
	}
	return error_state;

}


U8 DIO_set_port_value(U8 port_no,U8 port_value){
	U8 error_state=0;
	if(port_no >= DIO_Max_Port_no){
		error_state=1;
	}
	else if(port_value>DIO_Max_Port_value){
		error_state=1;
	}
	else{
		switch(port_no){
		case Group_A :
			DIO_U8_PORTA=port_value;
			break;
		case Group_B :
			DIO_U8_PORTB=port_value;
			break;
		case Group_C :
			DIO_U8_PORTC=port_value;
			break;
		case Group_D :
			DIO_U8_PORTD=port_value;
			break;

		}
	}
	return error_state;
}


U8 DIO_get_pin_value(U8 port_no,U8 pin_no,U8 *pin_value){
	U8 error_state=0;
	if(port_no >= DIO_Max_Port_no){
		error_state=1;
	}
	else if(pin_no >= DIO_Max_Pin_no){
			error_state=1;
		}
	else{
		switch(port_no){
		case Group_A :
			*pin_value=get_bit(DIO_U8_PINA,pin_no);
			break;
		case Group_B :
			*pin_value=get_bit(DIO_U8_PINB,pin_no);
			break;
		case Group_C :
			*pin_value=get_bit(DIO_U8_PINC,pin_no);
			break;
		case Group_D :
			*pin_value=get_bit(DIO_U8_PIND,pin_no);
			break;
		}
	}
	return error_state;

}
