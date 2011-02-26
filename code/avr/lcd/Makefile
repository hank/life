all:
	avr-gcc -g -Os -S -DF_CPU=4000000 -mmcu=attiny2313 -o main.S test.c
	avr-gcc -Os -DF_CPU=4000000 -mmcu=attiny2313 -o main.o test.c lcd.c -funroll-loops
	avr-objcopy -j .text -O ihex main.o main.hex
