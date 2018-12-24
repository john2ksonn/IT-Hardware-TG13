#include <LCD.h>
#include <at89c5131.h>

#define true 1
#define false !true
#define uint unsigned int

// change this to match the MCU
#define HIGH 0    // logic HIGH
#define LOW !HIGH // logic LOW

#define button P3 ^ 2 // interrupt0
#define min_dit_len 25
#define human_error_margin (min_dit_len / 10)

// stores the string as char array
// this could maybe be stored in EEPROM
const char morsecodetree[62] =
    "ETIANMSURWDKGOHVF#L#PJBXCYZQ##54#3###2#######16#######7###8#90";

unsigned int dit_len = 1;
int i;
char tmp_chars[4];
int wpm;
int temp_dit_len;
unsigned char first_run = true;

void reset_timer0();
void finish_char();
void add_element(uint element);

void init() {
    // READING SPEED SETTING FROM DIP SWITHES ON P3 (P3^4 - P3^7)
    //----------------------------------------------------------
    // 0xf0 = 0b11110000   (this is needed to only get the bits from the dip
    // switches) shifting everything four times to the right so that the first
    // dip switch is the LSB adding one so the range is from 1 to 16 rather than
    // 0 to 15 multiplying with min_dit_len
    dit_len = min_dit_len * (((P3 & 0xf0) >> 4) + 1);

    // INIT TIMER
    //----------
    // stop timer0
    TR0 = false;
    // 0x2 = 0b10 => 8 bit auto-reload timer
    TMOD = 0x2;
    // 250 microseconds until overflow
    TL0 = 5;
    TH0 = TL0;
    // enabling timer0 interrupt
    ET0 = true;

    // INIT EXTERNAL INTERRUPT
    //-----------------------
    // trigger on falling edge
    IT0 = false;
    // enabling external interrupt0
    EX0 = true;

    // enabling all interrupts
    EA = true;

    // start timer0
    TR0 = true;

    // INIT LCD
    //--------
    LCD_init();
    clear_LCD();
    select_first_line();
    wpm = (60000.0 / (dit_len * 50)) * 10;
    tmp_chars[3] = (wpm % 10) + 0x30;
    tmp_chars[2] = 0x2c;
    for (i = 1; i >= 0; i--) {
        wpm /= 10;
        tmp_chars[i] = (wpm % 10) + 0x30;
    }
    LCD_string(tmp_chars);
    LCD_string(" WPM | ");
    temp_dit_len = dit_len;
    for (i = 2; i >= 0; i--) {
        tmp_chars[i] = (temp_dit_len % 10) + 0x30;
        temp_dit_len /= 10;
    }
    tmp_chars[3] = 0x0;
    LCD_string(tmp_chars);
    LCD_string(" ms per dit");
    select_second_line();
    LCD_string("using \"PARIS\" with 50 elements");
    first_run = true;
}
