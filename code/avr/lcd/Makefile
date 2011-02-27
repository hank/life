all:
	avr-gcc -Os -DF_CPU=4000000 -mmcu=attiny2313 -o main.o test.c lcd.c
	avr-objcopy -R .fuse -R .lock -R .eeprom -O ihex main.o main.hex
