#include <iostream>
#include <stdlib.h>
#include <stdint.h>

// BOOST Random headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

// Other RNG stuff
#include <sys/time.h>

#include "tictactoe.cpp"

int main()
{
  TicTacToe t;
  // Movement variables
  uint8_t x, y;

  // BOOST Random generation support
  //boost::mt19937 gen;
  // Get current microseconds
  struct timeval tv;
  gettimeofday(&tv, NULL);
  boost::mt19937 gen(tv.tv_usec);
  boost::uniform_int<> dist(1, 3);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > 
    roll(gen, dist);

  while(1) {
    // Until we finish a game
    while(false == t.finished()) 
    {
      do 
      {
        // Move with PRNG
        x = roll();
        y = roll();
        // Make a move
      }
      while(!t.move(x,y));
      // Change the active player
      t.changePlayer();
      // Print the board
      t.printBoard();
    }
    // Game is finished.  Who won?
    t.printResult();
    // Continue?
    std::cout << "Press Enter to play again!\n";
    // Get a single character from the keyboard
    // If it's not a newline, break out of the while loop
    if(std::cin.get() != '\n') break;
    // Otherwise, clear the board and continue to the next game
    t.clearBoard();
  }
  return EXIT_SUCCESS;
}
