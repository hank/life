all: tic_random tic_interactive

tic_random: tic_random.cpp tictactoe.cpp tictactoe.h
	g++ -o $@ $<

tic_interactive: tic_interactive.cpp tictactoe.cpp tictactoe.h
	g++ -o $@ $<

clean:
	rm tic_random tic_interactive

