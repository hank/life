INPUTS=$(wildcard *.ooc)
TARGETS=$(patsubst %.ooc, %, $(INPUTS))

all: $(TARGETS)

%: %.ooc
	java -jar ~/repos/ooc/bin/ooc.jar $@
