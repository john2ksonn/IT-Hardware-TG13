#ifndef _METRONOM_ISRS_H_
#define _METRONOM_ISRS_H_

#include "at89c5131.h"
#include "default.h"
#include "config.h"

extern void LCD_string(unsigned char* Text);
extern void clear_LCD();

extern uchar bpm;

void resetTimer1();

#endif  //_METRONOM_ISRS_H_
