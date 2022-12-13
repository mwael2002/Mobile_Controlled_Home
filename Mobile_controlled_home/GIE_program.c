/*
 * GIE_program.c
 *
 *  Created on: Jul 5, 2022
 *      Author: mwael
 */
#include"STD_Types.h"
#include"bit_calc.h"
#include "GIE_interface.h"
#include "GIE_register.h"

void Global_Int_En_Dis(U8 Int_status){
	assign_bit(SREG,SREG_I,Int_status);
}
