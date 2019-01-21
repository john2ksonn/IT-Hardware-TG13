#include "AT89C5131.h"
#include "default.h"

extern void showBPM(uchar bpm);
extern void LCD_string(unsigned char* Text);
extern void clear_LCD();
extern void select_first_line();
extern void LCD_init();

void init();
