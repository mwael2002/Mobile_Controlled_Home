/*
 * LCD_interface.h
 *
 *  Created on: Sep 11, 2021
 *      Author: mwael
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_init(void);
void LCD_clear(void);

void shift_display_left(void);
void shift_display_right(void);
void shift_entire_display_right_initial_pos(void);

void LCD_move_curser_right(void);
void LCD_move_curser_left(void);
void LCD_move_curser_bottom(void);
void LCD_move_curser_top(void);

void LCD_write_char(U8 character);
void LCD_write_string(const char* str);
U8 LCD_write_string_pos(const char* string,U8 y_pos,U8 x_pos);
void LCD_write_no(U32 num);
void LCD_write_no_pos(U32 num,U8 y_pos,U8 x_pos);


#endif /* LCD_INTERFACE_H_ */
