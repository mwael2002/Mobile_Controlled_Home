/*
 * I2C_program.c
 *
 *  Created on: Nov 5, 2021
 *      Author: mwael
 */
#include"D:/C/bit_calc.h"
#include"D:/C/STD.Types.h"
#include"DIO_interface.h"
#include"I2C_private.h"
#include"I2C_interface.h"

void I2C_Master_init(void){
	TWSR=0b11111100; // freq 20 KHZ
	TWBR=0x07;
	TWCR=0b00000100;
}
void I2C_start(void){
	TWCR=0b10100100; // clear Interrupt flag
	                 // NACK
	                 // generate start condition
	                 // Enable I2C
	                 // Disable I2C Interrupt
	while(get_bit(TWCR,7)==0);
}
void I2C_Master_transmit_slave_address_write(U8 data){
	TWDR=data;
	TWCR=0b10000100;
	while(get_bit(TWCR,7)==0);
	//while((TWSR & 0xF8) !=0x18);
}
void I2C_Master_transmit_slave_address_read(U8 data){
	TWDR=data;
	TWCR=0b10000100;
	while(get_bit(TWCR,7)==0);
	//while((TWSR & 0xF8) !=0x40);
}
void I2C_Master_transmit(U8 data){
	TWDR=data;
	TWCR=0b10000100;
	while(get_bit(TWCR,7)==0);
}
void I2C_stop(void){
	TWCR=0b10010100;
}
char I2C_Master_Recieve_ACK(void){
TWCR=0b11000100;
while(get_bit(TWCR,7)==0);
return TWDR;
}
U8 I2C_Master_Recieve_data_NACK(void){
	TWCR=0b10000100;
	while(get_bit(TWCR,7)==0);
	return TWDR;
}
void I2C_Slave_init(U8 slave_address){
	TWAR=slave_address;
	TWCR=0b11000100; // enable I2C'
	                 // ACK
	                 // clear Interrupt flag
}
void I2C_Listen(void){
	while(get_bit(TWCR,7)==0);
}
void I2C_slave_transmit(U8 data){
	TWDR=data;
	TWCR=0b10000100;
	while(get_bit(TWCR,7)==0);
}
U8 I2C_Slave_Recieve_ACK(void){
	TWCR=0b11000100;
	while(get_bit(TWCR,7)==0);
	return TWDR;
}
U8 I2C_Slave_Recieve_NACK(void){
	TWCR=0b10000100;
		while(get_bit(TWCR,7)==0);
		return TWDR;
}
