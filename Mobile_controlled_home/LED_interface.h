/*
 * LED_interface.h
 *
 *  Created on: Sep 24, 2022
 *      Author: mwael
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

typedef struct{
	U8 LED_Port;
	U8 LED_Pin;
	U8 LED_Type;
}LED;

#define LED_Source    1
#define LED_Sink      0


U8 LED_init(LED* Copy_LED);
U8 LED_ON(LED* Copy_LED);
U8 LED_OFF(LED* Copy_LED);
U8 LED_Toggle(LED* Copy_LED);

#endif /* LED_INTERFACE_H_ */
