
sbit key = button;
uint last_state = LOW;
uint overflow_counter = 0;
uint milliseconds = 0;

void ext_int_0() interrupt 0 {
	//logic falling flank (button release)
	if (last_state == HIGH && key == LOW) {
		//dit
		if (milliseconds >= dit_len - human_error_margin && milliseconds <= dit_len - human_error_margin) {
			add_element(0);
		}
		//dah
		else if (milliseconds >= 3*(dit_len - human_error_margin) && milliseconds <= 3*(dit_len - human_error_margin)) {
			add_element(1);
		}
	}
	//logic rising flank (button press)
	else if (last_state == LOW && key == HIGH) {
		//character pause
		if (milliseconds >= 3*(dit_len - human_error_margin) && milliseconds <= 3*(dit_len - human_error_margin)) {
			finish_char();
		}
		//word pause
		else if (milliseconds >= 7*(dit_len - human_error_margin) && milliseconds <= 7*(dit_len - human_error_margin)) {
			finish_char();
			display_char(' ');
		}
	}
	reset_timer0();
	TR0 = true;
	last_state = key;
	P0 = last_state;
}

void timer_0() interrupt 1 {
	overflow_counter++;
	if (overflow_counter == 4){
		overflow_counter = 0;
		milliseconds++;
	}
}
