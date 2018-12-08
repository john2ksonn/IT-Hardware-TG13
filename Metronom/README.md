# Metronom

### Timer0 (for the timing):
        * 16bit
        * 1ms -> LowByte=0x03    Highbyte=0xE8
	* 1ms * 235 = 60000ms/255 = 235ms
        * 235ms * 255 = 59925
## Timer1 (for the buttons):
	* 16 bit
	* 1ms -> LowByte=0x03    HighByte=0xE8
	* 1ms * 100 = 100ms (for debouncing)
	* 1ms * 500 = 0.5s (for a long press)
	* 0.5 * 10 = 5s (for a longer press)
	
