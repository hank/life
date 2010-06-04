INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild

all: tic_random tic_interactive tictactoe_unittest

tictactoe_unittest: tictactoe_unittest.cpp tictactoe.h
	g++ -o $@ $< -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

tic_random: tic_random.cpp tictactoe.cpp tictactoe.h
	g++ -o $@ $<

tic_interactive: tic_interactive.cpp tictactoe.cpp tictactoe.h
	g++ -o $@ $<

clean:
	rm tic_random tic_interactive

