#include <main.h>

int char_index = -1;
// is needed to calc the last position (lastpos)
uint prior_options_count = 0;
unsigned char lastpos = 0;
unsigned char exponent = 0;

void main() {
    init();
    while (true)
        ;
}

void reset_timer0() {
    // stop timer0
    TR0 = false;
    TL0 = 5;
    TH0 = TL0;
    overflow_counter = 0;
    milliseconds = 0;
    TR0 = true;
}

// element == 0 => dit
// element == 1 => dah
void add_element(uint element) {
    char_index += calc_pow(2, exponent);
    char_index += lastpos;
    char_index += element;
    lastpos = char_index - prior_options_count;
    exponent += 1;
    prior_options_count += (2, exponent);
}

void finish_char() {
    if (char_index != -1) {
        LCD_send_d(morsecodetree[char_index]);
        char_index = -1;
        lastpos = 0;
        exponent = 0;
        prior_options_count = 0;
    }
}

int calc_pow(uint base, uint exponent) {
    unsigned char i;
    uint res;
    for (i = 0; i < exponent; i++) {
        res *= base;
    }
    return base;
}
