
int lockcode[3] = { 7, 1, 1 };
int tmp_lockcode[3] = { 0, 0, 0 };

/*#define S1 P1^0
#define S2 P1^1
#define H1 P1^4
#define H2 P1^5
#define H3 P1^6
#define H4 P1^7*/

#define S1 P3^0
#define S2 P3^1
#define H1 P0^0
#define H2 P0^1
#define H3 P0^2
#define H4 P0^3
#define H5 P0^4
#define H6 P0^5
#define H7 P0^6
#define H8 P0^7

#define true 1
#define false !true

int counter = 0;
int digit = 0;

void init();
void loop();
void delay(int t);
int checkCode();
void blinkLEDs();
void openLock();
void showNumber();
