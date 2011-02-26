include ../Makefile.inc
CFLAGS += -I../include
TARGETS=$(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c
	avr-gcc -c $(CFLAGS) -o $@ $<

all: $(TARGETS)

clean:
	rm lcd.o
