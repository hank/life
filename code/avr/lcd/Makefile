all:
	avr-gcc -c -Os -DF_CPU=4000000 -mmcu=attiny2313 -o lcd.o lcd.c
	avr-gcc -Os -DF_CPU=4000000 -mmcu=attiny2313 -o main.o test.c lcd.o
	avr-objcopy -j .text -O ihex main.o main.hex
