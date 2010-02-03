#
# Test Makefile for gpgme test application
# Nico Schottelius, 2007-08-05, GPLv3
#
flags=$(shell gpgme-config --libs --cflags)

#gpgme_test: gpgme_test.c
#	gcc -D_FILE_OFFSET_BITS=64 -g ${flags} $< -o $@
import_key.cgi: import_key.c
	gcc -D_FILE_OFFSET_BITS=64 -g ${flags} $< support.c -o $@ 
clean:
	rm -f gpgme_test import_key
