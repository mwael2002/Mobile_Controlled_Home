/*
 * I2C_program.c
 *
 *  Created on: Nov 5, 2021
 *      Author: mwael
 */
#include "STD_Types.h"
#include "bit_calc.h"
#include "TWI_register.h"
#include "TWI_config.h"
#include "TWI_private.h"
#include "TWI_interface.h"



void TWI_Master_init(void){

	//generate clock speed=400KHz with 8MHz system frequency
	//1-set bit rate register to 2
	TWBR=2;

	//2-clear the prescaler bits
	clear_bit(TWSR,TWPS0);
	clear_bit(TWSR,TWPS1);

	//disable Acknowledge bit generation
	clear_bit(TWCR,TWEA);

	//enable TWI
	set_bit(TWCR,TWEN);

}

void TWI_Slave_init(U8 Adderss){

	//assign the required address in 7MSB in the address register
	TWAR=Adderss<<1;

	//enable Acknowledge bit generation
	set_bit(TWCR,TWEA);

	//enable TWI
	set_bit(TWCR,TWEN);

}

TWI_Error_Status TWI_Send_Start_Condition(void){

	TWI_Error_Status  Local_Error=No_Error;
	U16 Error_counter=0;

	//send start condition on the bus
	set_bit(TWCR,TWSTA);

	//clear the interrupt flag to start the previous operation
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != START_ACK){

		Local_Error=Start_Condition_Error;
	}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Send_Repeated_Start(void){

	TWI_Error_Status Local_Error=No_Error;
	U16 Error_counter=0;

	//send start condition on the bus
	set_bit(TWCR,TWSTA);

	//clear the interrupt flag to start the previous operation
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != REP_START_ACK){

		Local_Error=Repeated_Start_Error;
	}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Send_Slave_Address_with_Write(U8 Slave_Address){

	TWI_Error_Status Local_Error=No_Error;
	U16 Error_counter=0;

	//set the required slave address in 7MSB on the bus
	TWDR=Slave_Address<<1;

	clear_bit(TWDR,0);

	//clear start condition bit
	clear_bit(TWCR,TWSTA);

	//clear the interrupt flag to start the previous operation
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != MASTER_TRANSMIT_SLAVE_ADDRESS_W_ACK ){

		Local_Error=Master_Slave_Address_Write_Error;
	}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Send_Slave_Address_with_Read(U8 Slave_Address){

	TWI_Error_Status Local_Error=No_Error;
	U16 Error_counter=0;

	//set the required slave address in 7MSB on the bus
	TWDR=Slave_Address<<1;

	set_bit(TWDR,0);

	//clear start condition bit
	clear_bit(TWCR,TWSTA);

	//clear the interrupt flag to start the previous operation
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != MASTER_TRANSMIT_SLAVE_ADDRESS_R_ACK ){

			Local_Error=Master_Slave_Address_Read_Error;
		}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Master_Write_Data_Byte(U8 Data){

	TWI_Error_Status Local_Error=No_Error;
	U16 Error_counter=0;

	//send the data on the bus
	TWDR = Data;

	//clear the interrupt flag to start the previous operation
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != MASTER_W_DATA_BYTE_ACK){

			Local_Error=Master_Write_Data_Byte_Error;
		}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Master_Read_Data_Byte_ACK(U8* Data){

	TWI_Error_Status Local_Error=No_Error;
	U16 Error_counter=0;

	//enable Acknowledge bit generation
	set_bit(TWCR,TWEA);

	//clear the interrupt flag to allow the slave to send the data
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != MASTER_R_DATA_BYTE_WITH_ACK){

			Local_Error=Master_Read_Data_Byte_Error_ACK;
		}

	else{
		//read the data
		*Data=TWDR;
	}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
    }

	return Local_Error;
}

TWI_Error_Status TWI_Master_Read_Data_Byte_NACK(U8* Data){

	TWI_Error_Status Local_Error=No_Error;
        U16 Error_counter=0;

	//clear the interrupt flag to allow the slave to send the data
	set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) != MASTER_R_DATA_BYTE_WITH_NACK){

			Local_Error=Master_Read_Data_Byte_Error_NACK;
		}

	else{
		//read the data
		*Data=TWDR;
	    }

	    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
	    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
	    }

	return Local_Error;
}


TWI_Error_Status TWI_Send_Stop_Condition(void){
         TWI_Error_Status Local_Error=No_Error;
  	 U16 Error_counter=0;

	//Set the stop condition bit
	set_bit(TWCR,TWSTO);

	//clear the interrupt flag to allow the slave to send the data
	set_bit(TWCR,TWINT);

	while((get_bit(TWCR,TWSTO)==1)&&(Error_counter<TWI_STOP_CONDITION_TIMEOUT)){
		Error_counter++;
	}

    if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Stop_Condition_Timeout_Error;
    }

   return Local_Error;

}





TWI_Error_Status TWI_check_Slave_Address_received_with_Write(void){

         TWI_Error_Status  Local_Error=No_Error;
         U16 Error_counter=0;

     	//enable Acknowledge bit generation
     	set_bit(TWCR,TWEA);
        set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) !=SLAVE_ADDRESS_RECEIVED_W ){

			Local_Error=TWI_SLAVE_Address_Received_W_Error;
		}

     if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
     }

return Local_Error;

   }


TWI_Error_Status TWI_Slave_Read_Data_Byte(U8* Data){

         TWI_Error_Status  Local_Error=No_Error;
         U16 Error_counter=0;

     	//enable Acknowledge bit generation
     	set_bit(TWCR,TWEA);
        set_bit(TWCR,TWINT);

	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) !=SLAVE_DATA_BYTE_RECEIVED){

			Local_Error=TWI_Slave_Data_Byte_Received_Error;
		}
	else{

	   *Data=TWDR;

	   }

     if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
    	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
     }

return Local_Error;

   }



TWI_Error_Status TWI_check_Slave_Address_received_with_Read(void){
    TWI_Error_Status  Local_Error=No_Error;
    U16 Error_counter=0;

	//enable Acknowledge bit generation
	set_bit(TWCR,TWEA);
   set_bit(TWCR,TWINT);



//wait until the operation complete and the flag is raised again
while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
	Error_counter++;
}

//check the operation status
if((TWSR & 0xF8) !=SLAVE_ADDRESS_RECEIVED_R){

		Local_Error=TWI_SLAVE_Address_Received_R_Error;
	}

if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
	Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
}

return Local_Error;
}

TWI_Error_Status TWI_Slave_Write_Data_Byte_NACK(U8 Data){

	TWI_Error_Status  Local_Error=No_Error;
    U16 Error_counter=0;

	TWDR=Data;
	clear_bit(TWCR,TWEA);
	set_bit(TWCR,TWINT);


	//wait until the operation complete and the flag is raised again
	while((get_bit(TWCR,TWINT)==0)&&(Error_counter!=TWI_WAIT_BUS_BUSY_TIMEOUT)){
		Error_counter++;
	}

	//check the operation status
	if((TWSR & 0xF8) !=SLAVE_DATA_BYTE_TRANSMITTED_NACK){

			Local_Error=TWI_Slave_Data_Byte_Transmitted_Error_NACK;
		}

	if(Error_counter==TWI_WAIT_BUS_BUSY_TIMEOUT){
		Local_Error=TWI_Wait_Bus_Busy_Timeout_Error;
	}

	return Local_Error;


}
