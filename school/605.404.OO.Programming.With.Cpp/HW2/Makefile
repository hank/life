INCLUDE=/home/hank/repos/life/code/cpp/testing/googletest-read-only/include
LIBS=/home/hank/repos/life/code/cpp/testing/googletest-read-only/scons/build/dbg/scons

all: poker_unittest test

#poker_unittest: poker_unittest.cpp pokerhand.h pokerhand.cpp card.h card.cpp
#	g++ -O3 -Wall -o $@ $< pokerhand.cpp card.cpp -I${INCLUDE} -L${LIBS} \
#			-lgtest -lgtest_main -lpthread
poker_unittest: poker_unittest.cpp pokerhand.h pokerhand.cpp card.h card.cpp
	g++ -O3 -Wall -o $@ $< pokerhand.cpp card.cpp -I${INCLUDE} \
			-L$(LIBS) -lgtest -lgtest_main

test: test.cpp pokerhand.h pokerhand.cpp card.h card.cpp
	g++ -o test test.cpp pokerhand.cpp card.cpp

clean:
	rm poker_unittest test

