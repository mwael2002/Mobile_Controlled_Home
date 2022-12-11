/*
 * LCD_private.h
 *
 *  Created on: Sep 11, 2021
 *      Author: mwael
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define init_right_top_limit 15
#define init_right_bottom_limit 79
#define init_left_top_limit 0
#define init_left_bottom_limit 64

static void LCD_send_data(U8 data);
static void LCD_send_cmd(U8 cmd);

#endif /* LCD_PRIVATE_H_ */
