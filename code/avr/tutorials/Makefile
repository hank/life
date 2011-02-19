MCU=attiny85
F_CPU=8000000# 8 MHz
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -I. -I../include -I/home/hank/repos/simavr/include -Wall -gdwarf-2
AVRFLAGS=-U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

TARGETS=$(patsubst %.c, %.hex, $(wildcard *.c))
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c
	$(CC) $(CFLAGS) -DF_CPU=$(F_CPU) -mmcu=$(MCU) $< -o $@

%.hex: %.o
	$(OBJCOPY) -j .text -O ihex $< $@ 

all: $(TARGETS) $(OBJS)

# You can do `make install some.hex` to just done one, of course
install: $(TARGETS)
	sudo avrdude $(AVRFLAGS) -c usbtiny -p t85 -e -U flash:w:$<

clean:
	rm -f *.o *.hex
