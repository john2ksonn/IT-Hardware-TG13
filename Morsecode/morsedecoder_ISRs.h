#include <at89c5131.h>

sbit key = button;
unsigned char overflow_counter = 0;
unsigned long milliseconds;
int tmp_ms;

//triggers on falling edge (button press)
void ext_int_0() interrupt 0 {
	if (!first_run){
		//character pause
		if (milliseconds >= 3*(dit_len - human_error_margin) && milliseconds <= 3*(dit_len - human_error_margin)) {
			finish_char();
		}
		//word pause
		else if (milliseconds >= 7*(dit_len - human_error_margin) && milliseconds <= 7*(dit_len - human_error_margin)) {
			finish_char();
			LCD_string(' ');
		}
		reset_timer0();
		while(key == HIGH);
			
		tmp_ms = milliseconds;
		for (i = 3; i >= 0; i--) {
			tmp_chars[i] = (tmp_ms%10) + 0x30;
			tmp_ms/=10;
		}
		LCD_string(tmp_chars);
		
		//dit
		if (milliseconds <= dit_len) {
			add_element(0);
			LCD_string("dit");
		}
		//dah
		else if (milliseconds >= 3*dit_len) {
			add_element(1);
			LCD_string("dah");
		}
	} else {
		clear_LCD();
		first_run = false;
		wait_500u(200);
	}
	reset_timer0();
}

void timer_0() interrupt 1 {
	overflow_counter++;
	if (overflow_counter == 4) {
		overflow_counter = 0;
		milliseconds++;
	}
}
