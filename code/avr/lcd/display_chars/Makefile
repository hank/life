LCDIESEL=/home/hank/repos/lcdiesel
CFLAGS=-Os -DF_CPU=8000000 -mmcu=attiny2313 -I$(LCDIESEL)/include -Wall -fno-unroll-loops

all:
	avr-gcc $(CFLAGS) -o display_chars.o display_chars.c $(LCDIESEL)/lib/lcd.o
	avr-objcopy -R .fuse -R .lock -R .eeprom -O ihex display_chars.o display_chars.hex

install:
	sudo avrdude -c usbtiny -p t2313 -e -U flash:w:display_chars.hex

clean:
	rm *.o *.hex
