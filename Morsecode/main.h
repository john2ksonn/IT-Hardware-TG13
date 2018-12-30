#ifndef _MAIN_H_
#define _MAIN_H_

#include "at89c5131.h"
#include "default.h"

extern unsigned char overflow_counter;
extern unsigned long milliseconds;
extern const char morsecodetree[62];
extern void init();
extern void LCD_string(unsigned char* Text);
extern void LCD_send_d(unsigned char Data);
void main();
void reset_timer0();
void add_element(uint element);
void finish_char();
int calc_pow(uint base, uint exponent);

#endif  //_MAIN_H_