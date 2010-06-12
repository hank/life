INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild

all: poker_unittest

test: test.cpp poker.h
	g++ -O3 -o $@ $<

poker_unittest: poker_unittest.cpp poker.h
	g++ -O3 -o $@ $< -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

clean:
	rm poker_unittest

