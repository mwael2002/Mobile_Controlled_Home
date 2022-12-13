/*
 * LED_program.c
 *
 *  Created on: Sep 24, 2022
 *      Author: mwael
 */
#include "STD_Types.h"
#include "bit_calc.h"
#include "LED_interface.h"
#include "DIO_interface.h"

U8 LED_init(LED* Copy_LED){
	U8 Error_State= OK;
		if(Copy_LED->LED_Pin <= DIO_Pin_7)
		{
			DIO_set_pin_direction(Copy_LED->LED_Port,Copy_LED->LED_Pin,OUTPUT);
		}
		else
		{
			Error_State=NOK;
		}
		return Error_State;
}




U8 LED_ON(LED* Copy_LED){
	U8 Error_State= OK;
		if(Copy_LED->LED_Pin <= DIO_Pin_7)
		{
			if(Copy_LED->LED_Type==LED_Source)
			   DIO_set_pin_value(Copy_LED->LED_Port,Copy_LED->LED_Pin,HIGH);
			else if(Copy_LED->LED_Type==LED_Sink)
				DIO_set_pin_value(Copy_LED->LED_Port,Copy_LED->LED_Pin,LOW);
		}
		else
		{
			Error_State=NOK;
		}
		return Error_State;

}

U8 LED_OFF(LED* Copy_LED){
	U8 Error_State= OK;
			if(Copy_LED->LED_Pin <= DIO_Pin_7)
			{
				if(Copy_LED->LED_Type==LED_Source)
				   DIO_set_pin_value(Copy_LED->LED_Port,Copy_LED->LED_Pin,LOW);
				else if(Copy_LED->LED_Type==LED_Sink)
					DIO_set_pin_value(Copy_LED->LED_Port,Copy_LED->LED_Pin,HIGH);
			}
			else
			{
				Error_State=NOK;
			}
			return Error_State;
}

U8 LED_Toggle(LED* Copy_LED){
	U8 Error_State= OK;
	static U8 LED_flag=0;
				if(Copy_LED->LED_Pin <= DIO_Pin_7)
				{
					DIO_set_pin_value(Copy_LED->LED_Port,Copy_LED->LED_Pin,toggle_bit(LED_flag,0));
				}
				else
				{
					Error_State=NOK;
				}
				return Error_State;

}

