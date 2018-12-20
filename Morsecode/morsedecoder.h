#define true 1
#define false !true
#define uint unsigned int

//change this to match the MCU
#define HIGH 0   //logic HIGH
#define LOW !HIGH   //logic LOW
	
#define button P3^2  //interrupt0
#define min_dit_len 50
#define human_error_margin (min_dit_len/10)

//stores the string as char array
//this could maybe be stored in EEPROM
const char morsecodetree[62] = "ETIANMSURWDKGOHVF#L#PJBXCYZQ##54#3###2#######16#######7###8#90";

unsigned int dit_len = 1;

void reset_timer0();
void display_char(char ch);
void finish_char();
void add_element(uint element);
void display_element(int element);

void init() {
	//READING SPEED SETTING FROM DIP SWITHES ON P3 (P3^4 - P3^7)
	//----------------------------------------------------------
	//0xf0 = 0b11110000   (this is needed to only get the bits from the dip switches)
	//shifting everything four times to the right so that the first dip switch is the LSB
	//adding one so the range is from 1 to 16 rather than 0 to 15
	//multiplying with min_dit_len
	dit_len = min_dit_len * (((P3 & 0xf0) >> 4) + 1);
	
	//INIT TIMER
	//----------
	//stop timer0
	TR0 = false;
	// 0x2 = 0b10 => 8 bit auto-reload timer
	TMOD = 0x2;
	//250 microseconds until overflow
	TL0 = 5;
	TH0 = TL0;
	//enabling timer0 interrupt
	ET0 = true;
	
	//INIT EXTERNAL INTERRUPT
	//-----------------------
	//trigger on rising and falling flank
	IT0 = true;
	//enabling external interrupt0
	EX0 = true;
	
	//enabling all interrupts
	EA = true;
}
