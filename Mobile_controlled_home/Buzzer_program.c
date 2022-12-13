/*
 * Buzzer_program.c
 *
 *  Created on: Sep 9, 2022
 *      Author: mwael
 */
#include "STD_Types.h"
#include "DIO_interface.h"
#include "Buzzer_config.h"
#include "Buzzer_interface.h"

void Buzzer_init(void){
	DIO_set_pin_direction(BUZZER_PORT, BUZZER_PIN, OUTPUT);
	DIO_set_pin_value(BUZZER_PORT, BUZZER_PIN, LOW);
}
void Buzzer_On(void){
	DIO_set_pin_value(BUZZER_PORT, BUZZER_PIN, HIGH);
}


void Buzzer_Off(void){
	DIO_set_pin_value(BUZZER_PORT, BUZZER_PIN, LOW);
}
