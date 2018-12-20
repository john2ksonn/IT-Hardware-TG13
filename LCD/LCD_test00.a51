/*
Prg: LCD_test00.a51
Datum: 9.12.18
Mit P3.0-P3.3 lassen sich verschiedene Funktione testen s. Kommentare
40stellig, 2 zeilig
Bei der Ausgabe eines Zeichens muss 'Daten' 1 bei Befehlen '0' sein.
Das Anzeigeram im LCD umfasst 80 Adressen, die aber nicht alle sichtbar sein müssen
(2*16). Die zweite Zeile beginnt deshalb bei 40. Für die Adressierung gilt
80h(10000000b=128)+Adresse. Das erste Bit muss immer 1 sein. Bsp: 1.Zeile-1. Zeichen-->80h; 
2.Zeile-1.Zeichen-->0A8h 2.Zeile -10. Zeichen-->178=0B2h. 
Wird der Cursor nicht gesetzt, wird automatisch das nächste Zeichen geschrieben. 
Schreibrichtung kann auch umgekehrt werden
Zum Testen kann mit den Tastern P3.0-P3.3 Text oder Cursorpositionen ausgegeben werden
Timer-Blinken ohne weitere Funktion
*/
 	offset equ 000h
	DSEG at 020h	;Bit-Variable definieren mit Bit-Adresse
LCD_out:	DS 1
	DSEG at 050h	;Bit-Variable definieren mit Bit-Adresse
T_counter0:	DS 1		;Zähler für Timer0-Int
T_counter1: DS 1
T_counter2:	DS 1	;Zähler für Verzögerungsschleifen
	var:	DS 1	
	bseg at 8h
Daten:		dbit 1	;Adresse 0-7 von LCD_out belegt
LCD_PORT  EQU P1 ; *** Hier den verwendeten Port einsetzen !!!!!!!!!!!! ******
;diese Werte sind von der Pinbelgegung abhängig---
RS		equ LCD_Port.0			;|
RW		equ LCD_Port.1			;|
E	  	equ LCD_Port.2			;|

busy			equ acc.7			;| busy wird an D7 eingelesen
;------------------------------------------------|

P_Zeile2	equ 192;			;Cursorposition für 2.Zeile links
 cseg
	org offset
	ljmp init
db 'LCD_test00.a51'			;Achtung bei externem Interrupt

	org 0bh	
	jmp T0_int

;************************************** Programm ***************************
init:  	mov   sp,#2fh		;Stackpointer oberhalb des Bitadressierbaren Bereichs
	mov tmod,#02		;Timer1 mode2
	mov th0,#6			;250us
	mov tl0,#6	
	mov T_counter0,#200	;Zähler für Timer0-Int
	mov T_counter1,#20	;Zähler für Timer0-Int
	setb et0			;Timer0 Int ein
	setb ea
	setb tr0		
	call zeit2			;warte 150ms
	lcall ResetLCD		;Displayreset
	lcall InitLCD		;Einstellung LCD 
;-----------------------------------------	
start:
;Abfrage der Taster
	call zeit2			;entprellen
;---------------------;Anzeige löschen
	jb p3.0,opt00		
	cpl p0.0			;zur Kontrolle
	call Display_delete
	call zeit2			;entprellen
	jnb p3.0,$			;warten bis taste losgelassen
;---------------------;Cursor 1.Zeile Position 1	
opt00:
	jb p3.1,opt01		
	cpl p0.1			
	call set_cursor0
	call zeit2			;entprellen
	jnb p3.1,$			;warten bis taste losgelassen
;---------------------;Cursor 2.Zeile mit Offset	
opt01:
	jb p3.2,opt02		
	cpl p0.2
	call set_cursor1
	call zeit2			;entprellen
	jnb p3.2,$			;warten bis taste losgelassen		
;---------------------,	Tesx ausgeben	
opt02:	
	jb p3.3,start	
	cpl p0.3
	call text	
	call zeit2			;entprellen
	jnb p3.3,$			;warten bis taste losgelassen	
	jmp start
;-----------------------------------------------------------------
;**************Zeile ausgeben
text:
	setb daten		;Daten RS=1	
	mov Lcd_out,#'L'	;Ausgabewert für Text
	call lcd		;Ausgeben
	call zeitl
	mov Lcd_out,#'C'
	call lcd
	call zeitl
	mov Lcd_out,#'D'
	call lcd
	call zeitl
	mov Lcd_out,#'_'
	call lcd
	call zeitl	
	mov Lcd_out,#'t'
	call lcd
	call zeitl	
	mov Lcd_out,#'e'
	call lcd
	call zeitl	
	mov Lcd_out,#'s'
	call lcd
	call zeitl	
	mov Lcd_out,#'t'
	call lcd
	call zeit2
	ret
;-----------------------------------------------------------------	
T0_int:		
	djnz T_counter0, back
		mov T_counter0,#200	;Zähler für Timer0-Int
		djnz T_counter1, back
			mov T_counter1,#20	;Zähler für Timer0-Int
			cpl p0.0
back:
	reti
;-----------------------------------------------------------------	
; **************** Display initialisieren ****************
; Display arbeitet im 2*4-Bit Modus
; Die 16 Zeichen belegen die Display-Adressen 00-0F und 40-4F (HEX!)
; Bit:    7       6       5       4       3       2      1      0
;      Register  Read/    0      Takt   D7/D3   D6/D2  D5/D1  D4/D0
;      Select    Write
ResetLCD:	
		mov LCD_PORT,#00110000b  	;wecken
		setb E			;Enable=1
		acall Zeitl		;mind 5 ms warten
		clr E			;Enable=0
		acall EnPuls 
		acall EnPuls
		ret
initlcd:
;umschalten auf 4-Bit
		clr daten
		mov LCD_PORT,#00100000b			;function_set  	8->4  BITS UMSCHALTEN, Takt=1
		acall EnPuls
;Function set 4 bits  
		mov LCD_out,#00101000b			;fourbitmode    	
		lcall LCD		;Ausgabe im 4Bit-Modus
; Display einstellen
		mov LCD_out,#00001100b    	; Display AN, Cursor AUS   	
		lcall LCD		;des Zeichens an der Cursorposition
		mov LCD_out,#00000110b    	; Not Shifted Display, Increment
		lcall LCD
		mov lcd_out,#00010000b		;Cursor move,left shift
		lcall lcd
		ret
;***********************************************************************
LCD:	mov a,LCD_out		;Ausgabewert in a
		anl A,#11110000b		;4 Bits maskieren
		mov LCD_PORT,A		;ausgeben
		mov c,daten		;bei Befehlen (Daten) ist RS=0(1)
		mov rs,c
		setb E			;Takt = 1
		setb E
		nop
		clr E			;Takt = 0
		mov a,LCD_out
		swap a
		anl A,#11110000b		;Low-Nibble
		mov LCD_PORT,A
		mov c,daten		;bei Befehlen (Daten) ist RS=0(1)
		mov rs,c
		setb E			;Takt = 1
		setb E
		nop
		clr E			;Takt = 0
;************** warten bis Bearbeitung im Display beendet **********
wbusy: 		clr rs			;Lesebefehl
		setb rw			;  ''
		setb e
		mov a,lcd_port		;Werte einlesen
		clr e
		nop
		setb e			;Lesebefehl wiederholen
		clr e
		jb busy,wbusy		;warten bis Display fertig
		ret 
;*************** Impuls an Enable Eingang ****************
EnPuls:		setb e
		acall Zeitk
		clr e
		ret
;*************** Zeitverzögerung ca 150 ms *****************
Zeit2:		mov r2,#30          	; ca. 150 msec warten     
Zeit20:		mov R1,#10
zeit21:     	djnz T_counter2,zeit21
		djnz R1,zeit21
		djnz r2,zeit20
		ret
;*************** Zeitverzögerung ca 5 ms *****************
Zeitl:		mov R1,#10          		; ca. 5 msec warten     
w0:    	 	djnz T_counter2,w0
		djnz R1,w0
		ret
;*************** Zeitverzögerung ca 100 us *****************
Zeitk:
w2:		djnz R1,$           		; wartet 100 usec
		ret		

;*************** Zeile(16 Zeichen) löschen *****************
clearline:
	mov r7,#16
	setb daten		;Daten RS=1	
ausg3:	mov lcd_out,#' '	;Ausgabewert für Text
	call lcd		;Ausgeben
	djnz r7,ausg3
	clr daten
	ret
;UP
;Display löschen
Display_delete:
	clr daten
	mov lcd_out,#1			;cleardisplay
	lcall lcd
	call zeitl
	ret
set_cursor0:
;Cursor in Zeile1
	clr daten
	mov lcd_out,#02	;Cursorposition 1.Zeile
	call lcd		;Ausgeben
	ret
set_cursor1:	
;Cursor setzen
	clr daten				;Befehl
	mov lcd_out,#P_Zeile2+10		;Cursorposition	 2.Zeile links+Offset
	call lcd
	ret
;-----------------------------------------


;****** PIN-Belegung für LCD-Display LTN 214 R-10 am LCD_PORT **************
; * Uebertragung eines Bytes als 2 * 4 Bits.
; * Ansicht von oben auf Display
; * 1 GND--------------------------------------------------> GND
; * 2 +5Volt-----------------------------------------------> +5V
; * 3 V0: Steuerspannung Kontrast 0..5 Volt erlaubt,-------> V0 
; *       Arbeitspunkt ca. 0.6 V (am besten Spindeltrimmer zum Einst.)
; * 4 RS: Registersatz (Display oder Befehl)---------------> LCD_PORT.0
; * 5 R/W: Schreiben oder lesen----------------------------> LCD_PORT.1
; * 6 E: Uebergabetakt-------------------------------------> LCD_PORT.2
; * 7-10: frei (eigentlich D0 - D3, wird aber nicht verwendet)
; * 11: D4/D0----------------------------------------------> LCD_PORT.4
; * 12: D5/D1----------------------------------------------> LCD_PORT.5
; * 13: D6/D2----------------------------------------------> LCD_PORT.6
; * 14: D7/D3----------------------------------------------> LCD_PORT.7
; *******************************************************
		  end