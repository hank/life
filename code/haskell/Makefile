CC=ghc
OBJS :=$(patsubst %.hs,%.o,$(wildcard *.hs))
RESULTS :=$(patsubst %.hs,%,$(wildcard *.hs))
TEMPS :=$(patsubst %.hs,%.hi,$(wildcard *.hs))

all: $(RESULTS)
	rm -f $(TEMPS)

clean:
	rm -f $(OBJS) $(RESULTS)

%.o: %.hs
	$(CC) -c $<
