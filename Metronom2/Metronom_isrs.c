#include "Metronom_isrs.h"

uint btnInc_milliseconds = 0;
uint btnDec_milliseconds = 0;
uint milliseconds = 0;
uchar overflow_counter0 = 0;

sbit btn0 = btnInc;
sbit btn1 = btnDec;

uchar btnFlags = 0x00;
uchar beatFlag = 0;

void resetTimer1() {
    TR1 = false;
    TH1 = 0x3c;
    TL1 = 0xb0;
    btnInc_milliseconds = 0;
    btnDec_milliseconds = 0;
    TR1 = true;
}

void ext_int0() interrupt 0 {
    // set the flag for btn0
    btnFlags = 0x01;
    resetTimer1();
}

void timer_0() interrupt 1 {
    overflow_counter0++;
    if (overflow_counter0 == 4) {
        milliseconds++;
        overflow_counter0 = 0;
    }

    if (milliseconds >= (60000 / bpm)) {
        output = 0x00;
        beatFlag = 1;
        milliseconds = 0;
    } else if (beatFlag && milliseconds == 100) {
        output = 0xff;
        beatFlag = 0;
    }
}

void ext_int1() interrupt 2 {
    // set the flag for btn1
    btnFlags = 0x02;
    resetTimer1();
}

void timer_1() interrupt 3 {
    if (btnFlags & 0x01 && btn0 == HIGH) {
        if ((btnInc_milliseconds % 500) == 0) {
            if (btnInc_milliseconds < 5000)
                bpm++;
            else
                bpm += 5;
            if (bpm < maxBPM) bpm = maxBPM;
        }
        btnInc_milliseconds++;
    } else if (btnFlags & 0x02 && btn1 == HIGH) {
        if ((btnDec_milliseconds % 500) == 0) {
            if (btnDec_milliseconds < 5000)
                bpm--;
            else
                bpm -= 5;
            if (bpm < 1) bpm = 1;
        }
        btnDec_milliseconds++;
    } else if (btnFlags & 0x01 && btn0 == LOW) {
        btnInc_milliseconds = 0;
        btnFlags &= 0xfe;
    } else if (btnFlags & 0x02 && btn1 == LOW) {
        btnDec_milliseconds = 0;
        btnFlags &= 0xfd;
    }

    TH1 = 0x3c;
    TL1 = 0xb0;
}
