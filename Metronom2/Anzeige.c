#include "Anzeige.h"

extern unsigned char bpm;
uint i;
char tmp_chars[3];
int tmp_bpm;

#ifdef LCD
void showBPM(uchar bpm) {
    clear_LCD();
    select_first_line();
    tmp_bpm = bpm;
    for (i = 2; i >= 0; i--) {
        tmp_chars[i] = (tmp_bpm % 10) + 0x30;
        tmp_bpm /= 10;
    }
    LCD_string(tmp_chars);
}
#endif  // LCD

#ifdef ICM7212
void showBPM(uchar bpm) {
    // TODO
}
#endif  // ICM7212
