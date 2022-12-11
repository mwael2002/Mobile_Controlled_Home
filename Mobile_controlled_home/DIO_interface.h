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
#define Port_8_pins_INPUT 0
#define Port_8_pins_OUTPUT 255


#define HIGH 1
#define LOW 0
#define Port_HIGH 255
#define Port_LOW 0


#define DIO_Pin_0  0
#define DIO_Pin_1  1
#define DIO_Pin_2  2
#define DIO_Pin_3  3
#define DIO_Pin_4  4
#define DIO_Pin_5  5
#define DIO_Pin_6  6
#define DIO_Pin_7  7



U8 DIO_set_pin_value(U8 port_no,U8 pin_no,U8 pin_value);
U8 DIO_set_pin_direction(U8 port_no,U8 pin_no,U8 pin_direction);
U8 DIO_set_port_value(U8 port_no,U8 port_value);
U8 DIO_set_port_direction(U8 port_no,U8 port_direction);
U8 DIO_get_pin_value(U8 port_no,U8 pin_no,U8 *pin_value);
U8 DIO_get_port_value(U8 port_no,U8 *port_value);

#endif /* DIO_INTERFACE_H_ */
