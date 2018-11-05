//Ampel 2

#include <Ampel2.h>
#include <AT89C5131.h>

bit wait = false; //wait for a delay
bit busy = false; //the cpu is busy performing the cycle
unsigned int one_mill_sec_counter = 2;
unsigned int delay_time; //time in milliseconds to wait


//TODO
//Triggering with the external interrupt 0 (INT0) does not work


sbit main_green = main_road_green;
sbit main_yellow = main_road_yellow;
sbit main_red = main_road_red;
sbit side_green = side_road_green;
sbit side_yellow = side_road_yellow;
sbit side_red = side_road_red;

sbit sensor1 = P3^2;
sbit sensor2 = P3^3;

void side_road_1() interrupt 0 {
	if(!wait && !busy)
		cycle();
	sensor1 = 1;
}

void side_road_2() interrupt 2 {
	if(!wait && !busy)
		cycle();
	sensor2 = true;
}

void timer_0() interrupt 1 {
	//after 4 interrupts (4*500us=1millisecond)...
	one_mill_sec_counter--;
	if(one_mill_sec_counter == 0){
		one_mill_sec_counter = 4;
		//...decrease the delay_time and check if it is zero
		delay_time--;
		if(delay_time == 0){
			wait = false;
			TR0 = false;
		}
	}
}

void main() {
	init();
	while(true);
}

void init() {
	//init traffic lights
	P1 = 0xc3; //0b11000000 => side road red; main road green; sensors high
	
	//init timer0
	TR0 = 0;
	TMOD = 0x2; // 0b00000010 => 8 bit auto-reload timer
	TL0 = 0x6; //250 microseconds
	TH0 = TL0;
	
	//enable external interrupts
	EX0 = 1;
	IT0 = 1; //trigger int0 on high to low
	EX1 = 1;
	IT1 = 1; //trigger int1 on high to low
	
	//enabel timer0 interrupt
	ET0 = 1;
	
	EA = 1; //enable all interrupts globally
}

void delay (int arg) {
	delay_time = arg;
	TR0 = true;
	wait = true;
}

void cycle() {
	busy = true;
	main_yellow = true;
	main_green = false;
	side_yellow = true;
	side_red = false;
	//delay(1000); //wait 1000 milliseconds
	delay(1);
	while(wait);
	main_red = true;
	main_yellow = false;
	side_green = true;
	side_yellow = false;
	//delay(3000); //wait 3000 milliseconds
	delay(1);
	while(wait);
	side_yellow = true;
	side_green = false;
	main_yellow = true;
	main_red = false;
	//delay(1000); //wait 1000 milliseconds
	delay(1);
	while(wait);
	side_red = true;
	side_yellow = false;
	main_green = true;
	main_yellow = false;
	//delay(5000); //start 5000 milliseconds timer
	delay(5);
	busy = false;
}

