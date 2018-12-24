// change this to match the MCU
#define HIGH 0     // logic HIGH
#define LOW !HIGH  // logic LOW

#define button P3 ^ 2  // interrupt0

#define human_error_margin (min_dit_len / 10)

#define min_dit_len 25
