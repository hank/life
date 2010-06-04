INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild
hugeint_unittest: hugeint_unittest.cpp hugeint.h
	g++ -o $@ $< -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

test: test.cpp hugeint.h
	g++ -o $@ $<

all: test hugeint_unittest
