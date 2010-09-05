CC= gcc
CFLAGS= -Wall -g -I/usr/include/GNUstep/
LDFLAGS= -lobjc -lgnustep-base
LD	= gcc
FRACTION	= fraction
SRCS	= main.m Fraction.m

HEADS	= $(SRCS:.m=.h)
OBJS	= $(SRCS:.m=.o)
all: $(FRACTION)

clean:
	$(RM) $(RMFLAGS) $(OBJS) $(FRACTION)

$(FRACTION): $(OBJS)
	$(CC) $(LDFLAGS) -o $(FRACTION) $(OBJS)

.SUFFIXES:.o .m
.m.o:
	$(CC) -c $(CFLAGS) $< 
