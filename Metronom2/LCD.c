#include "lcd.h"

sbit RS = LCD_Port ^ 0;  // RS Steuersignal
sbit RW = LCD_Port ^ 1;  // Lesen /schreiben
sbit E = LCD_Port ^ 2;   // Enable
sbit LCD_D4 = LCD_Port ^ 4;
sbit LCD_D5 = LCD_Port ^ 5;
sbit LCD_D6 = LCD_Port ^ 6;
sbit LCD_D7 = LCD_Port ^ 7;

void wait_500u(unsigned int k) {
    unsigned char j;
    unsigned int l;
    for (l = 0; l < k; l++) {
        for (j = 0; j < 162; j++) {
        }
    }
}
void LCD_init() {
    wait_500u(300);  // 150ms warten
    RS = 0;          // Steuercodes senden
    RW = 0;
    E = 0;
    LCD_send_b(0x28);
    E = 1;
    E = 0;
    LCD_send_b(0x28);
    LCD_send_b(0x0c);
    LCD_send_b(1);  // Anzeige löschen
}
void LCD_send_b(unsigned char Data)  // Senden eines Befehls
{
    RS = 0;
    RW = 0;
    LCD_send(Data);
}
void LCD_send_d(unsigned char Data)  // Senden von Anzeigedaten
{
    RW = 0;
    RS = 1;
    LCD_send(Data);
}
void LCD_send(unsigned char Data) {
    unsigned char busy = 1;  // zur Abfrage des Busy-flags
    LCD_D7 = Data & 0x80;    // linkes Bit ausgeben
    Data <<= 1;              // links schieben
    LCD_D6 = Data & 0x80;    // linkes Bit ausgeben
    Data <<= 1;              // links schieben
    LCD_D5 = Data & 0x80;    // linkes Bit ausgeben
    Data <<= 1;              // links schieben
    LCD_D4 = Data & 0x80;    // linkes Bit ausgeben
    Data <<= 1;              // links schieben
    E = 1;                   // schreibbefehl
    _nop_();                 // kurze Wartezeit
    E = 0;
    LCD_D7 = Data & 0x80;  // linkes Bit ausgeben
    Data <<= 1;            // links schieben
    LCD_D6 = Data & 0x80;  // linkes Bit ausgeben
    Data <<= 1;            // links schieben
    LCD_D5 = Data & 0x80;  // linkes Bit ausgeben
    Data <<= 1;            // links schieben
    LCD_D4 = Data & 0x80;  // linkes Bit ausgeben
    Data <<= 1;            // links schieben
    E = 1;                 // schreibbefehl
    _nop_();               // kurze Wartezeit
    E = 0;
    // Busy flag abfragen
    LCD_D7 = 1;  // als Eingang schalten
    while (busy) {
        RS = 0;
        RW = 1;
        E = 1;
        busy = LCD_D7;
        E = 0;
        E = 1;  // zweiter Lesebefehl
        E = 0;
    }
}
// Ausgabe eines Strings	an der aktuellen Cursorposition
void LCD_string(unsigned char* Text) {
    unsigned char i;
    // Ausgabe bis 0-Zeichen kommt
    for (i = 0; Text[i] != 0; i++) {
        LCD_send_d(Text[i]);
    }
}

void clear_LCD() { LCD_send_b(1); }

void select_first_line() { LCD_send_b(0x80 + 0); }

void select_second_line() { LCD_send_b(0x80 + 0x40); }
