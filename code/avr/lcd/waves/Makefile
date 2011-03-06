LCDIESEL=/home/hank/repos/lcdiesel
CFLAGS=-Os -DF_CPU=8000000 -mmcu=attiny2313 -I$(LCDIESEL)/include -Wall -fno-unroll-loops
all:
	avr-gcc $(CFLAGS) -o xbm_display.o xbm_display.c $(LCDIESEL)/lib/lcd.o
	avr-objcopy -R .fuse -R .lock -R .eeprom -O ihex xbm_display.o xbm_display.hex

install:
	sudo avrdude -c usbtiny -p t2313 -e -U flash:w:xbm_display.hex
