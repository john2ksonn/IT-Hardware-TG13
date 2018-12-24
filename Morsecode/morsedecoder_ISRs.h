#ifndef _MORSEDECODER_ISRS_H_
#define _MORSEDECODER_ISRS_H_

#include "at89c5131.h"
#include "default.h"
#include "config.h"

extern unsigned char first_run;
extern unsigned int dit_len;
extern unsigned int dit_len;
extern char tmp_chars[4];
extern int i;

extern void finish_char();
extern void reset_timer0();
extern void add_element(uint element);
extern void LCD_string(unsigned char* Text);
extern void clear_LCD();
extern void wait_500u(unsigned int k);

#endif //_MORSEDECODER_ISRS_H_
