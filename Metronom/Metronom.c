#include <Metronom.h>
#include <Anzeige.h>

//declaring counter0 and counter1 for timer0
int t0c0 = 0;
int t0c1 = 0;

//declaring counter0 for timer1
int t1c0 = 0;
int stepCount = 0;

int bpm = defaultBPM;
int diff;

sbit outPin = outputPin;
sbit incBpmBtn = T1;
sbit decBpmBtn = T2;

//ISR for timer0
void timer0() interrupt 1 {
	t0c0++;
	if (t0c0 == 60000/maxBPM) {
		t0c0 = 0;
		t0c1++;
		if (t0c1 == (maxBPM + 1 - bpm)){
			t0c1 = 0;
			outPin = HIGH;
		}
	}
	//set the pin to LOW after the defined onTime passed (default is 100ms)
	else if (t0c0 == onTime) {
		outPin = LOW;
	}
	//reload
	TL0 = 0x18;
	TH0 = 0xfc;;
}

void timer1() interrupt 3 {
	t1c0++;
	//wait until a half second passed
	if(t1c0 > 500) {
		diff = 0;
		// if the incBpmBtn is still pressed...
		if (incBpmBtn == HIGH){
			//...depending on how many steps already got registered...
			if (stepCount < 10){
				//...either increase the diff by one...
				diff++;
			} else {
				//...or by five.
				diff += 5;
			}
			//increase the stepCount
			stepCount++;
		}
		//this is almost the same
		else if (decBpmBtn == HIGH){
			if (stepCount < 10){
				diff--;
			} else {
				diff -= 5;
			}
			stepCount++;
		}
		//if the button got released...
		else {
			//...stop the timer and reset the counter
			TR1 = false;
			stepCount = 0;
		}
		
		//add the diff to the current bpm while considiring the boundaries
		if (bpm + diff > maxBPM)
			setBPM(maxBPM);
		else if (bpm + diff < minBPM)
			setBPM(minBPM);
		else
			setBPM(bpm + diff);
	}
	
	//reload
	TL0 = 0x18;
	TH0 = 0xfc;
}

void main() {
	init();
	loop();
}

void loop() {
	while(true) {
		
		// if exactly one of the buttons got pressed (XOR) and the timer isn't running yet...
		if ((incBpmBtn^decBpmBtn)&& TR1 == false){
			//...start the timer
			TR1 = true;
		}
	}
}


//this method changes the bpms ans updates the display
void setBPM(int newBPM){
	bpm = newBPM;
	showBPMs(bpm);
}
