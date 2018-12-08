#include <AT89C5131.h>

sbit displayPort = outputPort;

void showBPMs(int bpm) {
	int output;
	int i;
	for (i = 0; i < 4; i++){
		//select the digit
		output = 1 << 4+i;
		//get only one digit by using the modulo operator...
		//...and perform a bitwise OR
		output |= bpm%10;
		//move the next digit to position 0 by dividing by 10
		bpm/=10;
		
		//write it to the port
		displayPort = output;
	}
}