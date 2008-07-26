INCLUDES=-I/usr/include/pango-1.0 \
-I/usr/include/cairo \
-I/usr/lib/glib-2.0/include \
-I/usr/include/glib-2.0 \
-I/usr/include/gtk-2.0 \
-I/usr/lib/gtk-2.0/include \
-I/usr/include/atk-1.0 \
-I/usr/local/include/clutter-0.8

LIBDIR=-L/usr/local/lib
LIBS=-lclutter-glx-0.8 -lgtk-x11-2.0 -lclutter-gtk-0.8

all: main

main: main.c
	$(CC) $(INCLUDES) $(LIBDIR) -o $@ $< $(LIBS)

clean: main
	rm $<
