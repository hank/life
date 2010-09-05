INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild
SOURCES=hugeint_unittest.cpp hugeint.cpp

#hugeint_unittest: hugeint_unittest.cpp hugeint.h hugeint.cpp
#	g++ -g -O0 -o $@ $(SOURCES) -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

test: test.cpp hugeint.h hugeint.cpp
	g++ -o $@ hugeint.cpp $<

all: test
