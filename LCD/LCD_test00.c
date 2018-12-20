/*++++++++++++++++++++++++++++++++++++++++++
Dateiname:	LCD_test.c
Autor:	G.Wild	                  +
Datum:	9.12.18
Initialisiert die Anzeige
Pinbelegung ist in LCD_dec.festgelegt
P3.0: Cursor Zeile1 Position 10 mit Textausgabe
P3.1: Anzeige löschen
P3.2: Cursor Zeile1 Position 0 mit Stunden Minuten Ausgabe
P3.3:CUrsor Zeile1 Position1 mit Textausgabe
In der Endlosschleife werden verschiedene Ausgaben gemacht
++++++++++++++++++++++++++++++++++++++++++*/
//	#include <stdio.h>
	#include <at89c5131.h>

/**************Befehlsbeispiele
//	LCD_send_b(0x07);	//Display shift	links
//	LCD_send_b(0x05);	//Display shift	rechts= von rechts nach links schreiben
//	LCD_send_b(0x06);	//Display shift	aus;	nach rechts schreiben
//	LCD_send_b(1);	//Anzeige löschen zurück auf 1. Zeile Position 1	1640us
//  LCD_send_b(0x80+n);	 //n=0h..27h; n=0-->Cursor Anfang erste Zeile
// LCD_send_b(0x80+40);	 //n=40h..67h;n=40hCursor Anfang zweite Zeile


***********************************/
	sfr LCD_Port = 0x90;		//Ganzer Port1

sbit  RS 		= LCD_Port^0;     //RS Steuersignal
sbit  RW 		= LCD_Port^1;			//Lesen /schreiben
sbit  E  		= LCD_Port^2;			//Enable
sbit  LCD_D4	= LCD_Port^4;
sbit  LCD_D5	= LCD_Port^5;
sbit  LCD_D6	= LCD_Port^6;
sbit  LCD_D7	= LCD_Port^7;

sbit T1=P3^0;
sbit T2=P3^1;
sbit T3=P3^2;
sbit T4=P3^3;
 
void wait_500u(unsigned int k );
void LCD_send_b(unsigned char Data);
void LCD_send_d(unsigned char Data);
void LCD_send(unsigned char Data);
void LCD_string(unsigned char *Text);
void Lcd_place(unsigned char Pos,unsigned char *Text_var1,unsigned char *Text_var2);
extern void          _nop_     (void);
void Init_LCD();
void LCD_init();
//void Lcd_place(unsigned char Pos,unsigned char *Text_var1,unsigned char *Text_var2);
//void Lcd_place(unsigned char Pos,unsigned char *Text_var);
 char T_Zeile1[]="  Dies ist Zeile1                       ";
 char T_Zeile2[]="und dies      zeile2                    ";

//*Deklaration der Funktionen und Varianlem*********
	#define Zeile2 192
	unsigned char Zahl;
	unsigned char Stunde[]="12";
	unsigned char Minute[]="23"	 ;
	unsigned char Sekunde=0;
	unsigned char Temp_BW[]="44";
	unsigned char Temp_Hz[]="45";
	unsigned char Temp_Vorl[]="46";
	unsigned int Timer_count=100;
	bit test;
	Text_Z1=5;
	Text_Z2=5;
//**************************************************
void main ()
{	
	TMOD=0x01;
	ET0=1;
	TR0=1;
    TH0=0xd8;					//10 ms
    TH1=0xf0;
 
	EA=1;	

    test=1;
	LCD_init();
//Zum Testen können die folgenden Befehl einzeln einkommentiert werden
//	LCD_send_b(0x07);	//Display shift	links
//	LCD_send_b(0x05);	//Display shift	rechts= von rechts nach links schreiben
//	LCD_send_b(0x06);	//Display shift	aus;	nach rechts schreiben
//	LCD_send_b(1);	//Anzeige löschen zurück auf 1. Zeile Position 1	1640us
	LCD_send_b(1);	//Anzeige löschen zurück auf 1. Zeile Position 1	1640us
	  LCD_send_b(0x80+0);	 //auf erste Zeile
	//LCD_string(T_Zeile1);	 //Text für Zeile1 senden
	LCD_string("hier gehts los ");
		LCD_string("hier gehts weiter");
   	LCD_send_b(0x80+0x40);	 //auf zweite Zeile
	LCD_string(Stunde);	 //Text für Zeile1 senden
		LCD_string(":");
	LCD_string(Minute);		
	
	while(1)
	{ 	  	


	if (!T1)
	{LCD_send_b(0x80+10);	 //auf erste Zeile
		LCD_string("hier gehts los");}
	if (!T2) LCD_send_b(1);	 //Anzeige löschen
	if (!T3)
		{LCD_send_b(192);	 //auf zweite Zeile
	LCD_string(Stunde);	 //Text für Zeile1 senden
		LCD_string(":");
	LCD_string(Minute);	}
		if(!T4)
		{	LCD_send_b(0x80);	 //auf erste Zeile
		LCD_string("ganz links");
		}

		/*	LCD_place(3,Temp_BW,T_Zeile1);	//Die Variable Tem_BW wird ab Position3 in den Text für Zeile1 eingefügt
	LCD_place(14,Temp_Vorl,T_Zeile1);
	LCD_place(25,Stunde,T_Zeile1);
	LCD_place(28,Minute,T_Zeile1);*/
	/*
		LCD_string(T_Zeile1);   //Text ausgeben


	LCD_send_b(Zeile2+3);	//Position
	LCD_send_d(Temp_BW[0]);//Brauchwassertemperatur ausgeben
	LCD_send_d(Temp_BW[1]);
	LCD_send_d(210);	//°-Zeichen	ausgeben

	LCD_send_b(Zeile2+14);	//Position
	LCD_send_d(Temp_Vorl[0]);//Brauchwassertemperatur
	LCD_send_d(Temp_Vorl[1]);
	LCD_send_d (210);	//°-Zeichen

	LCD_send_b(Zeile2+25);	 //auf zweite Zeile Position 30
	LCD_send_d(Stunde[0]);
	LCD_send_d(Stunde[1]);
	LCD_send_b(Zeile2+28);	 //auf zweite Zeile Position 33
	LCD_send_d(Minute[0]);
	LCD_send_d(Minute[1]);


//	LCD_send_d(Byte_BCD(Sekunde,2)+48);	//BCD-Einer bestimmen ASCii-Korrektur und senden
//	LCD_send_d(Byte_BCD(Sekunde,1)+48);	//BCD-Einer bestimmen ASCii-Korrektur und senden
  */

	  }
		

}

//***************************************************
void wait_500u(unsigned int k )
{ unsigned char j;
  unsigned int l;
  for (l=0;l<k;l++)
  {	for (j=0;j<162;j++)
	{}}}
void LCD_init()
{ 	wait_500u(300);		//150ms warten
	RS=0;				//Steuercodes senden
	RW=0;
	E=0;
	LCD_send_b(0x28);
	E=1;
	E=0;
	LCD_send_b(0x28);
	LCD_send_b(0x0c);
	LCD_send_b(1);	//Anzeige löschen 
	}
void LCD_send_b(unsigned char Data)		//Senden eines Befehls
 {	RS=0;
 	RW=0;
	LCD_send(Data);}
void LCD_send_d(unsigned char Data)	//Senden von Anzeigedaten
 {	RW=0;
 	RS=1;
	LCD_send(Data);}
void LCD_send(unsigned char Data)
{  	unsigned char busy=1;	//zur Abfrage des Busy-flags
	LCD_D7= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D6= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D5= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D4= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   E=1;						//schreibbefehl
   E=1;					   //kurze Wartezeit
  _nop_();
   E=0;
   LCD_D7= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D6= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D5= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   LCD_D4= Data&0x80;		//linkes Bit ausgeben
   Data<<=1;				//links schieben
   E=1;						//schreibbefehl
   _nop_();					   //kurze Wartezeit
   E=0;
//Busy flag abfragen
   LCD_D7=1;			//als Eingang schalten
   while(busy)
     { RS=0;
       RW=1;
       E=1;	
	   busy=LCD_D7;
	   E=0;
	   E=0;
	   E=1;			//zweiter Lesebefehl
	   E=0;} }
//+++++++++++++++++++++++++++++
//Ausgabe eines Strings	an der aktuellen Cursorposition
 void LCD_string(unsigned char *Text) 
	{unsigned char  i; 
	  for (i=0;Text[i]!=0;i++)	//Ausgabe bis 0-Zeichen kommt
       { LCD_send_d(Text[i]); }			  }
//++++++++++++++++++++++++++++++++
/*text2 in in text1 eingefügt wobei Pos die Position angibt ab, der
text2 eingefügt wird.
Aufruf: string_place(n,text2,text1)			*/
void lcd_place(unsigned char Pos,char *text_in, char *text_out)
{  unsigned char i;
   for (i=0;text_in[i]!=0;i++)
   {text_out[i+Pos]=text_in[i];}}
//+++++++++++++++++++++++++++++
/*text2 wird in text1 eingefügt, wobei Pos die Position angibt ab, der
text2 eingefügt wird.
Aufruf: string_place(n,text2,text1)			*/
void string_place(unsigned char Pos,char *text_in, char *text_out)
{  unsigned char i;
   for (i=0;text_in[i]!=0;i++)
   {text_out[i+Pos]=text_in[i];}}
//							   */
	 
	 //***************************************************
void timer0 (void) interrupt 1
//	 void timer0 (void) interrupt 1	//Timer0 Int
{ TH0=0xd8;
  TH1=0xf0;
	Timer_count--;
	if(Timer_count==0)
		{
		P0=~P0;
		Timer_count=100;
			Minute[1]++;
			if (Minute[1]==0x3a) 
				{Minute[1]=0x30;
				 Minute[0]++;}

			
	//		LCD_send_b(0x80+50);	 //auf zweite Zeile Position 10
//	LCD_string(printf(Timer_count));	 //Text für Zeile1 senden
}}