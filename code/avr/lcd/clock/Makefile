LCDIESEL=/home/hank/repos/lcdiesel
LCDIESEL_LIB=$(LCDIESEL)/lib
LCDIESEL_INCLUDE=$(LCDIESEL)/include
CFLAGS=-Os -DF_CPU=8000000 -mmcu=attiny2313a -I$(LCDIESEL_INCLUDE)
all: 
	avr-gcc $(CFLAGS) -o main.o test.c $(LCDIESEL_LIB)/lcd.o
	avr-objcopy -j .text -j.data -O ihex main.o main.hex
