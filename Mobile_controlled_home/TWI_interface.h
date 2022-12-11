/*
 * TWI_interface.h
 *
 *  Created on: Sep 23, 2022
 *      Author: mwael
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum{

	No_Error,
	Start_Condition_Error,
	Repeated_Start_Error,
	Master_Slave_Address_Write_Error,
	Master_Slave_Address_Read_Error,
	Master_Write_Data_Byte_Error,
	Master_Read_Data_Byte_Error_ACK,
	Master_Read_Data_Byte_Error_NACK,
	TWI_Wait_Bus_Busy_Timeout_Error,
	TWI_Stop_Condition_Timeout_Error,
    TWI_SLAVE_Address_Received_W_Error,
	TWI_SLAVE_Address_Received_R_Error,
    TWI_Slave_Data_Byte_Received_Error,
	TWI_Slave_Data_Byte_Transmitted_Error_NACK,

}TWI_Error_Status;


void TWI_Master_init(void);
TWI_Error_Status TWI_Send_Start_Condition(void);
TWI_Error_Status TWI_Send_Repeated_Start(void);
TWI_Error_Status TWI_Send_Slave_Address_with_Write(U8 Slave_Address);
TWI_Error_Status TWI_Send_Slave_Address_with_Read(U8 Slave_Address);
TWI_Error_Status TWI_Master_Write_Data_Byte(U8 Data);
TWI_Error_Status TWI_Master_Read_Data_Byte_ACK(U8* Data);
TWI_Error_Status TWI_Master_Read_Data_Byte_NACK(U8* Data);
TWI_Error_Status TWI_Send_Stop_Condition(void);

void TWI_Slave_init(U8 Adderss);
TWI_Error_Status TWI_check_Slave_Address_received_with_Write(void);
TWI_Error_Status TWI_Slave_Read_Data_Byte(U8* Data);
TWI_Error_Status TWI_check_Slave_Address_received_with_Read(void);
TWI_Error_Status TWI_Slave_Write_Data_Byte_NACK(U8 Data);

#endif /* TWI_INTERFACE_H_ */
