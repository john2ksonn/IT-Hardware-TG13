#include <AT89C5131.h>

#define true 1
#define false !true
	

//logical HIGH and logical LOW
//change this to match the hardware
#define HIGH 1 //if the pins are highactive
//#define HIGH 0 //if the pins are lowactive
#define LOW !HIGH

#define T1 P0^0
#define T2 P0^1

#define minBPM 1
#define maxBPM 255
#define defaultBPM 60

//define the pin to output the signal
#define outputPin P0^7
//define the output port for the 7 segment display
#define outputPort P1

//define how long the pin should stay on HIGH for each beat (in milliseconds)
#define onTime 100

void loop();
void setBPM(int newBPM);

void init() {
	//init both timers in mode1 (16 bit) 
	TMOD = 0x11; //0b00010001
	
	//init both timers with 1ms
	TL0 = 0x03;
	TH0 = 0xE8;
	TL1 = TL0;
	TL1 = TH0;
	
	//enable the timers' interrupts
	ET0 = 1;
	ET1 = ET0;
	//enable all interrupts globally
	EA = 1;
	
	TR0 = 1;
}

