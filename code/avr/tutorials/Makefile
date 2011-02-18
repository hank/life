MCU=attiny85
F_CPU=8000000# 8 MHz
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -I.

TARGETS=$(patsubst %.c, %.hex, $(wildcard *.c))

%.o: %.c
	$(CC) $(CFLAGS) -DF_CPU=$(F_CPU) -mmcu=$(MCU) $< -o $@

%.hex: %.o
	$(OBJCOPY) -j .text -O ihex $< $@ 

all: $(TARGETS)

clean: $(TARGETS)
	rm $<
