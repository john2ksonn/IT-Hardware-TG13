#include <morsedecoder_isrs.h>

sbit key = button;
unsigned char overflow_counter = 0;
unsigned long milliseconds;
int tmp_ms;
unsigned char pressed_flag = false;
unsigned char waiting = true;

void init_isrs() {
    // INIT TIMER
    //----------
    // stop timer0
    TR0 = false;
    // 0x2 = 0b10 => 8 bit auto-reload timer
    TMOD = 0x2;
    // 250 microseconds until overflow
    TL0 = 5;
    TH0 = TL0;
    // setting timer0 int priority to high
    PT0L = 1;
    // enabling timer0 interrupt
    ET0 = true;

    // INIT EXTERNAL INTERRUPT
    //-----------------------
    // trigger int1 on falling edge (button press)
    IT0 = true;
    // setting ext int0 priority to low
    PX0L = 0;
    // enabling external interrupt0
    EX0 = true;
    // trigger int1 on falling edge (button press)
    IT1 = true;
    // enabling external interrupt1
    EX1 = true;
    // enabling all interrupts
    EA = true;
    // start timer0
    TR0 = true;
}

// triggers on falling edge (button press)
void ext_int_0() interrupt 0 {
    if (first_run) {
        clear_LCD();
        first_run = false;
        wait_500u(200);
    } else {
        pressed_flag = true;
        waiting = false;
    }
    reset_timer0();
}

void timer_0() interrupt 1 {
    overflow_counter++;
    if (overflow_counter == 4) {
        overflow_counter = 0;
        milliseconds++;
    }

    if (!first_run && key == LOW && pressed_flag) {
        pressed_flag = false;
        waiting = false;
        // dit
        if (milliseconds < 3 * dit_len) {
            add_element(0);
        }
        // dah
        else if (milliseconds >= 3 * dit_len) {
            add_element(1);
        }
        reset_timer0();
    } else if (!pressed_flag && !first_run && !waiting) {
        // word pause
        if (milliseconds >= 7 * dit_len) {
            LCD_string(" ");
            waiting = true;
        }
        // character pause
        else if (milliseconds >= 3 * dit_len) {
            finish_char();
        }
    }
}

// triggers on falling edge (button press)
void ext_int_1() interrupt 2 { clear_LCD(); }
