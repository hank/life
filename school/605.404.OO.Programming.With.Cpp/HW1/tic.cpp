#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <exception>

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
  uint8_t x, y;
  char c;

  // BOOST Random generation support
  //boost::mt19937 gen;
  // Get current microseconds
  struct timeval tv;
  gettimeofday(&tv, NULL);
  boost::mt19937 gen(tv.tv_usec);
  boost::uniform_int<> dist(0, 2);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > roll(gen, dist);

  while(1) {
    // Until we finish a game
    while(false == t.finished()) 
    {
      // use PRNG for testing.
      x = roll();
      y = roll();
      // Make a move
      t.move(x,y);
      // Change the active player
      t.change_player();
      t.print_board();
    }
    // Game is finished.  Who won?
    t.print_result();
    // Continue?
    printf("Press Enter to play again!\n");
    c = getc(stdin);
    if(c != '\n') break;
    t.clear();
  }
  return EXIT_SUCCESS;
}
