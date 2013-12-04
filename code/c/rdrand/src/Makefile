OPENSSL=/usr/local/Cellar/openssl/1.0.1e
OPENSSL_INCLUDE=$(OPENSSL)/include
OPENSSL_LIB=$(OPENSSL)/lib
INCLUDES=-I../librdrand-1.1 -I$(OPENSSL_INCLUDE)
LIBS=-L../librdrand-1.1 -L$(OPENSSL_LIB)
TARGETS=create_good_random
SOURCES=create_good_random.c
OBJS=$(SOURCES:.c=.o)

%.o: %.c
	$(CC) -c $(INCLUDES) -o $@ $<

create_good_random: $(OBJS)
	$(CC) $(LIBS) $(INCLUDES) -o $@ $(OBJS) -lrdrand -lssl -lcrypto

all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(TARGETS) $(OBJS)
