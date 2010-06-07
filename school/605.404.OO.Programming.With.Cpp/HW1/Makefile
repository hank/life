INCLUDE=../../../code/cpp/testing/googletest-read-only/include
LIBS=../../../code/cpp/testing/googletest-read-only/mybuild

all: tic_random tic_1player tic_2player tictactoe_unittest

tictactoe_unittest: tictactoe_unittest.cpp tictactoe.h
	g++ -O3 -o $@ $< -I${INCLUDE} -L${LIBS} -lgtest -lgtest_main -lpthread

tic_random: tic_random.cpp tictactoe.cpp tictactoe.h
	g++ -O3 -o $@ $<

tic_2player: tic_2player.cpp tictactoe.cpp tictactoe.h
	g++ -O3 -o $@ $<

tic_1player: tic_1player.cpp tictactoe.cpp tictactoe.h
	g++ -O3 -o $@ $<

clean:
	rm tic_1player tic_2player tic_random tictactoe_unittest

