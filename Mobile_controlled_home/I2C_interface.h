/*
 * I2C_interface.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mwael
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_
void I2C_Master_init(void);
void I2C_Master_transmit_slave_address_write(U8 data);
void I2C_Master_transmit_slave_address_read(U8 data);
void I2C_Master_transmit(U8 data);
void I2C_start(void);
void I2C_start_inturrupt(void);
void I2C_stop(void);
char I2C_Master_Recieve_ACK(void);
U8 I2C_Master_Recieve_data_NACK(void);
void I2C_Slave_init(U8 Slave_Address);
void I2C_Listen(void);
char* interrupt_re(void);
#endif /* I2C_INTERFACE_H_ */
