#include <AT89C5131.h>
#include <morsedecoder.h>
#include <morsedecoder_ISRs.h>

int char_index = -1;
uint prior_options_count = 0;  // is needed to calc the last position (lastpos)
uint lastpos = 0;
uint power = 0;

void main() {
	init();
	while(true);
}

void reset_timer0() {
	//stop timer0
	TR0 = false;
	TL0 = 5;
	TH0 = TL0;
	overflow_counter = 0;
	milliseconds = 0;
	TR0 = true;
}

//element == 0 => dit
//element == 1 => dah
void add_element(uint element) {
	char_index += 2^power;
	char_index += lastpos;
	char_index += element;
	lastpos = char_index - prior_options_count;
	power += 1;
	prior_options_count += 2^power;
}

void finish_char() {
	char tmp_char[1];
	tmp_char[0] = morsecodetree[char_index];
	LCD_string(tmp_char);
	char_index = -1;
	lastpos = 0;
	power = 0;
	prior_options_count = 0;
}

