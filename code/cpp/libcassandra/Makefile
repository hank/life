all: example1

example1: example1.cpp
	g++ --std=gnu++0x -o $@ $< -lcassandra -lthrift \
         -I/usr/local/include/thrift
