INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild

all: poker_unittest

poker_unittest: poker_unittest.cpp pokerhand.h pokerhand.cpp card.h card.cpp
	g++ -O3 -Wall -o $@ $< pokerhand.cpp card.cpp -I${INCLUDE} -L${LIBS} \
			-lgtest -lgtest_main -lpthread

clean:
	rm poker_unittest

