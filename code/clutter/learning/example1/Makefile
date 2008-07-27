CFLAGS=`pkg-config clutter-0.8 --cflags`
LIBS=`pkg-config clutter-0.8 --libs`
CFLAGS+= -I/usr/local/include/clutter-0.8
CC=gcc

all: main

main: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean: main
	rm $<
