# IT Hardware TG 13/4
## Cheatsheet
### Chip

    AT89C5131A

### Startup popup
Startup? -> Nein

### ROM im Debugger auslesen:

* Reiter "Memory 1" vom Fenster unten rechts öffnen
* "c:0" in Leiste eingeben ('0' entspricht der Adresse)

### Wichtig
`#include <AT89C5131.h>`

### AT89C5131-V2010 Jumpers
* K8: Jumper for enabling the LEDs on Port 0
* K13: Jumper for power supply

## LCD Pinout

1. VSS (GND)
2. VDD (5V)
3. VEE (Contrast)
4. RS 
5. R/W
6. E
7. DB0
8. DB1
9. DB2
10. DB3
11. DB4
12. DB5
13. DB6
14. DB7
15. LEDA
16. LEDK

## AT89C5131-V2010 Pinout
1. GND
2. VCC (5V)
3. Pn^0
4. Pn^1
5. Pn^2
6. Pn^3
7. Pn^4
8. Pn^5
9. Pn^6
10. Pn^7


### Connection
| LCD | MCU |
|-----|-----|
|VSS|GND|
|VDD|VCC|
|VEE|GND|
|RS|Pn^0|
|R/W|Pn^1|
|E|Pn^2|
|DB4|Pn^4|
|DB5|Pn^5|
|DB6|Pn^6|
|DB7|Pn^7|
