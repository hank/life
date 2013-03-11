CFLAGS=-O3 -Wall
TARGETS=example1_server example1_client
all: $(TARGETS)

example1_server: example1_server.cpp
	$(CXX) $(CFLAGS) -o $@ $<

example1_client: example1_client.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean: 
	rm -f $(TARGETS)
