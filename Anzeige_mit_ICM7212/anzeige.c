#include <AT89C5131.h>

#define true 1
#define false !true

int z[4] = {0, 4, 2, 0};

sbit displayPort = P0;

void main(){
	int i;
	int output;
	while(true){
		for(i=0; i<4; i++) {
			output = 1 << 4+i;
			output |= z[i];
			displayPort = output;
		}
	}
}
