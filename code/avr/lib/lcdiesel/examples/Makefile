include ../Makefile.inc
CFLAGS += -I../include
TARGETS=$(patsubst %.c, %.hex, $(wildcard *.c))
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $< ../lib/lcd.o

%.hex: %.o
	$(OBJCOPY) $(OBJCOPYFLAGS) -j .text -O ihex $< $@

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJS)

flash_test_1:
	sudo avrdude -c usbtiny -p t2313 -e -U flash:w:test_1.hex
