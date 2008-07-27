CFLAGS=`pkg-config clutter-0.8 --cflags`
LIBS=`pkg-config clutter-0.8 --libs` -lgtk-x11-2.0 -lclutter-gtk-0.8
CFLAGS+= -I/usr/local/include/clutter-0.8
CFLAGS+= -I/usr/lib/gtk-2.0/include
CFLAGS+= -I/usr/include/atk-1.0
CC=gcc

all: main

main: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean: main
	rm $<
