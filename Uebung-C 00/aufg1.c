//Ampel1

#include <AT89C5131.h>
	//sbit ausgang=0x90;
	sbit ausgang=P1^0;
	
void main(){
	while(1){
		unsigned int i;
		//ausgang=~ausgang;
		ausgang = 0;
		for(i=0;i<116279;i++);
		ausgang = 1;
	}
}
