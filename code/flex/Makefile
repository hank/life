MXMLC = /home/hank/tmp/flex/bin/mxmlc
MFLAGS = -debug=true
TARGETS  = hello.swf FirstCircle.swf MovingCircle.swf
 
all: $(TARGETS)
 
clean:
	$(RM) $(TARGETS)
 
.SUFFIXES:    .as .swf
.as.swf:
	$(MXMLC) $(MFLAGS) $<
