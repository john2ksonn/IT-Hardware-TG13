#include "Metronom2.h"

uchar bpm = 60;

void main() {
    LCD_init();
    init();
    while (true)
        ;
}

void init() {
    // Timer init
    //-----------
    // causes timer0 to overflow every millisecond
    TH0 = 0x06;
    TL0 = 0x06;
    // causes timer1 to overflow every 50 milliseconds
    TH1 = 0x3c;
    TL1 = 0xb0;
    // timer0 mode1 (16bit) & timer1 mode1 (16bit)
    TMOD = 0x12;
    // enable timer0 interrupt
    ET0 = true;
    // enable timer1 interrupt
    ET1 = true;

    // Buttons init
    //-------------
    // enable ext INT0 for btnInc on P3^2
    EX0 = true;
    // trigger ext INT0 on falling edge
    IT0 = true;
    // enable ext INT1 for btnDec on P3^3
    EX1 = true;
    // trigger ext INT1 on falling edge
    IT1 = true;
    // enable all interrupts
    EA = true;

    // start timer0
    TR0 = true;
}
