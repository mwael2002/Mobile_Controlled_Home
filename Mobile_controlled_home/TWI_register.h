/*
 * TWI_register.h
 *
 *  Created on: Sep 23, 2022
 *      Author: mwael
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

#define TWBR          *((volatile U8*)0x20)

#define TWCR          *((volatile U8*)0x56)
#define TWINT    7
#define TWEA     6
#define TWSTA    5
#define TWSTO    4
#define TWWC     3
#define TWEN     2
#define TWIE     0

#define TWSR          *((volatile U8*)0x21)
#define TWPS1    1
#define TWPS0    0

#define TWDR          *((volatile U8*)0x23)

#define TWAR          *((volatile U8*)0x22)
#define TWGCE    0

#endif /* TWI_REGISTER_H_ */
