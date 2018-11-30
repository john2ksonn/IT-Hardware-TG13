#include <Codeschloss.h>
#include <AT89C5131.h>

sbit led1 = H1;
sbit led2 = H2;
sbit led3 = H3;
sbit led4 = H4;
sbit led5 = H5;
sbit led6 = H6;
sbit led7 = H7;
sbit led8 = H8;
sbit button1 = S1;
sbit button2 = S2;

bit wait = false;

unsigned int one_mill_sec_counter = 4;
unsigned int delay_time; //time in milliseconds to wait

void timer_0() interrupt 1 {
	//after 4 interrupts (4*250us=1millisecond)...
	one_mill_sec_counter--;
	if(one_mill_sec_counter == 0){
		one_mill_sec_counter = 4;
		//...decrease the delay_time and check if it is zero
		delay_time--;
		if(delay_time == 0){
			TR0 = false;
			wait = false;
		}
	}
}

void main(){
	init();
	while (true){
		loop();
	}
}

void init(){
	led1 = 1;
	led2 = 1;
	led3 = 1;
	led4 = 1;
	
	//init timer0
	TR0 = 0;
	TMOD = 0x2; // 0b00000010 => 8 bit auto-reload timer
	TL0 = 5; //250 microseconds
	TH0 = TL0;
	ET0 = 1;
	EA = 1;	
}

void loop(){
	if (button1 == 0){
		delay(250);
		if(counter < 8){
			counter++;
		}
		else
			counter = 0;
	}
	if (button2 == 0){
		delay(250);
			tmp_lockcode[digit] = counter;
			digit++;
			counter = 0;
		if(digit == 3){
			tmp_lockcode[digit] = counter;
			digit = 0;
			counter = 0;
			if(checkCode())
				openLock();
			else
				blinkLEDs();
			tmp_lockcode[0] = tmp_lockcode[1] = tmp_lockcode[2] = 0;
		}
	}
	showNumber();
}

//wait for t milliseconds
void delay (int arg) {
	delay_time = arg;
	TR0 = true;
	wait = true;
	while(wait);
}

void showNumber(){
	led1 = !(counter >= 1);
	led2 = !(counter >= 2);
	led3 = !(counter >= 3);
	led4 = !(counter >= 4);
	led5 = !(counter >= 5);
	led6 = !(counter >= 6);
	led7 = !(counter >= 7);
	led8 = !(counter == 8);
}

int checkCode(){
	int i;
	for (i = 0; i < 3; i++)
		if(lockcode[i] != tmp_lockcode[i])
			return false;
	return true;
}

void openLock(){
	led1 = led2 = led3 = led4 = led5 = led6 = led7 = led8 = 0;
	delay(3000);
	led1 = led2 = led3 = led4 = led5 = led6 = led7 = led8 = 1;
}

void blinkLEDs(){
	int i;
	led1 = led2 = led3 = led4 = led5 = led6 = led7 = led8 = 1;
	delay(1000);
	for(i = 0; i < 3; i++)	{
		led1 = led2 = led3 = led4 = led5 = led6 = led7 = led8 = 0;
		delay(10);
		led1 = led2 = led3 = led4 = led5 = led6 = led7 = led8 = 1;
		delay(1000);
	}
}
