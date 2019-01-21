#ifndef _ANZEIGE_H_
#define _ANZEIGE_H_

#include "AT89C5131.h"
#include "default.h"

#define LCD
#ifndef LCD
#define ICM7212
#endif  // LCD

#ifdef LCD
extern void clear_LCD();
extern void LCD_string(unsigned char *Text);
extern void select_first_line();
#endif //LCD

void showBPM(uchar bpm);

#endif  //_ANZEIGE_H_
