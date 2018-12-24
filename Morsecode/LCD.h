#ifndef _LCD_H_
#define _LCD_H_

#include <at89c5131.h>

#define LCD_Port P1

extern void _nop_(void);

void wait_500u(unsigned int k);
void LCD_send_b(unsigned char Data);
void LCD_send_d(unsigned char Data);
void LCD_send(unsigned char Data);
void LCD_string(unsigned char* Text);
void LCD_init();
void clear_LCD();
void select_second_line();
void select_first_line();

#endif  //_LCD_H_
