/*
 * TWI_private.h
 *
 *  Created on: Sep 23, 2022
 *      Author: mwael
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define START_ACK                             0x08 /* start has been sent */
#define REP_START_ACK                         0x10 /* repeated start */

#define MASTER_TRANSMIT_SLAVE_ADDRESS_W_ACK   0x18 /* Master transmit ( slave address + Write request ) ACK */
#define MASTER_TRANSMIT_SLAVE_ADDRESS_R_ACK   0x40 /* Master transmit ( slave address + Read request )  ACK */
#define MASTER_W_DATA_BYTE_ACK                0x28 /* Master transmit data ACK */
#define MASTER_R_DATA_BYTE_WITH_ACK           0x50 /* Master received data with ACK */
#define MASTER_R_DATA_BYTE_WITH_NACK          0x58 /* Master received data with NACK */


#define SLAVE_ADDRESS_RECEIVED_R              0xA8 /* means that slave address is received with read request */
#define SLAVE_ADDRESS_RECEIVED_W              0x60 /* means that slave address is received with write request */
#define SLAVE_DATA_BYTE_RECEIVED              0x80 /* means that a byte is received */
#define SLAVE_DATA_BYTE_TRANSMITTED_ACK       0xB8 /* means that the written byte is transmitted with ACK*/
#define SLAVE_DATA_BYTE_TRANSMITTED_NACK      0xC0 /* means that the written byte is transmitted with ACK*/

#endif /* TWI_PRIVATE_H_ */
