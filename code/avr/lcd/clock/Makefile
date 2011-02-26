CFLAGS=-I..
all: 
	avr-gcc $(CFLAGS) -Os -DF_CPU=4000000 -mmcu=attiny2313 -o main.o test.c ../lcd.c
	avr-objcopy -j .text -O ihex main.o main.hex
