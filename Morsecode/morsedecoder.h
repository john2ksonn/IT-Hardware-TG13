#ifndef _MORSEDECODER_H_
#define _MORSEDECODER_H_

#include "at89c5131.h"
#include "default.h"
#include "config.h"

extern void LCD_init();
extern void clear_LCD();
extern void LCD_string(unsigned char* Text);
extern void select_first_line();
extern void select_second_line();

void init();

#endif  //_MORSEDECODER_H_
