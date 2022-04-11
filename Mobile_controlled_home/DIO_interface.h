/*
  * DIO_interface.h
 *
 *  Created on: Sep 10, 2021
 *      Author: mwael
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define Group_A 0
#define Group_B 1
#define Group_C 2
#define Group_D 3
#define DIO_Max_Port_no 4
#define DIO_Max_Pin_no 8
#define DIO_Min_Port_value 0
#define DIO_Max_Port_value 255
#define DIO_Min_Port_direction 0
#define DIO_Max_Port_direction 255
#define INPUT 0
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define DIO_Pin_A0  0
#define DIO_Pin_A1  1
#define DIO_Pin_A2  2
#define DIO_Pin_A3  3
#define DIO_Pin_A4  4
#define DIO_Pin_A5  5
#define DIO_Pin_A6  6
#define DIO_Pin_A7  7

#define DIO_Pin_B0  0
#define DIO_Pin_B1  1
#define DIO_Pin_B2  2
#define DIO_Pin_B3  3
#define DIO_Pin_B4  4
#define DIO_Pin_B5  5
#define DIO_Pin_B6  6
#define DIO_Pin_B7  7

#define DIO_Pin_C0  0
#define DIO_Pin_c1  1
#define DIO_Pin_C2  2
#define DIO_Pin_C3  3
#define DIO_Pin_C4  4
#define DIO_Pin_C5  5
#define DIO_Pin_C6  6
#define DIO_Pin_C7  7

#define DIO_Pin_D0  0
#define DIO_Pin_D1  1
#define DIO_Pin_D2  2
#define DIO_Pin_D3  3
#define DIO_Pin_D4  4
#define DIO_Pin_D5  5
#define DIO_Pin_D6  6
#define DIO_Pin_D7  7
U8 DIO_set_pin_value(U8 port_no,U8 pin_no,U8 pin_value);
U8 DIO_set_pin_direction(U8 port_no,U8 pin_no,U8 pin_direction);
U8 DIO_set_port_value(U8 port_no,U8 port_value);
U8 DIO_set_port_direction(U8 port_no,U8 port_direction);
U8 DIO_get_pin_value(U8 port_no,U8 pin_no,U8 *pin_value);
U8 DIO_get_port_value(U8 port_no,U8 *port_value);
#endif /* DIO_INTERFACE_H_ */
