/*
 * DIO_private.h
 *
 *  Created on: Sep 10, 2021
 *      Author: mwael
 */

#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define DIO_U8_PINA *((volatile U8*)0x39)
#define DIO_U8_DDRA *((volatile U8*)0x3A)
#define DIO_U8_PORTA *((volatile U8*)0x3B)

#define DIO_U8_PINB *((volatile U8*)0x36)
#define DIO_U8_DDRB *((volatile U8*)0x37)
#define DIO_U8_PORTB *((volatile U8*)0x38)

#define DIO_U8_PINC *((volatile U8*)0x33)
#define DIO_U8_DDRC *((volatile U8*)0x34)
#define DIO_U8_PORTC *((volatile U8*)0x35)

#define DIO_U8_PIND *((volatile U8*)0x30)
#define DIO_U8_DDRD *((volatile U8*)0x31)
#define DIO_U8_PORTD *((volatile U8*)0x32)






#endif /* DIO_REGISTER_H_ */
