HTML := $(patsubst %.rdoc,%.html,$(wildcard *.rdoc))

all: $(HTML)

clean: $(HTML)
	rm $<

%.html: %.rdoc
	rdoc -1 $< > $@

