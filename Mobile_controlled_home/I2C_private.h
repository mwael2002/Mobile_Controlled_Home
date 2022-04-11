/*
 * I2C_private.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mwael
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_
#define TWAR *((volatile U8*)0x22)
#define TWBR *((volatile U8*)0x20)
#define TWCR *((volatile U8*)0x56)
#define TWDR *((volatile U8*)0x23)
#define TWSR *((volatile U8*)0x21)
#define SREG *((volatile U8*)0X5F)

#endif /* I2C_PRIVATE_H_ */
