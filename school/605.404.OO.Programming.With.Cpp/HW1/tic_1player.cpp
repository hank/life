#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include "tictactoe.h"

// BOOST Random headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

// Other RNG stuff
#include <sys/time.h>

int main()
{
  TicTacToe t;
  // Movement variables
  unsigned int x, y;
  std::stringstream ss;
  std::string input;

  // BOOST Random generation support
  // Seed with current microseconds
  struct timeval tv;
  gettimeofday(&tv, NULL);
  boost::mt19937 gen(tv.tv_usec);
  boost::uniform_int<> dist(1, 3);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > roll(gen, dist);

  while(1) {
    // Until we finish a game
    std::cout << "To move, put row (1-3) then column (1-3) like so: 1 3" 
              << std::endl;
    std::cout << "Then press Enter." << std::endl;
    while(false == t.finished()) 
    {
      t.printBoard();
      do 
      {
        if('X' == t.getCurrentPlayer())
        {
          std::cout << t.getCurrentPlayer() << "'s move: ";
          // Read X and Y from command line
          while(getline(std::cin, input))
          {
            // Clear error state of string stream
            ss.clear();
            // Clear the old string
            ss.str("");
            // Parse the x and y params from the line
            ss << input;
            if(ss >> x >> y)
            {
              // Proper input
              if(!t.isInBounds(x, y))
              {
                std::cout << "Space was out of bounds.  Try again." << std::endl
                          << t.getCurrentPlayer() << "'s move: ";
                continue;
              }
              if(t.occupied(x, y))
              {
                std::cout << "Space was already occupied.  Try again." << std::endl
                          << t.getCurrentPlayer() << "'s move: ";
                continue;
              }
              else
              {
                // Wonderful.  Make the move.
                break;
              }
            }
            else
            {
              // Bad input
              std::cout << "Bad input.  Try again." << std::endl;
              std::cout << t.getCurrentPlayer() << "'s move: ";
            }
          }
          // Make sure we haven't received an EOF
          if(std::cin.eof())
          {
            // Exit
            std::cout << "\nExiting..." << std::endl;
            exit(EXIT_SUCCESS);
          }
          // Make a move
        }
        else
        {
          std::cout << t.getCurrentPlayer() << "'s move" << std::endl;
          // Query PRNG until we get an unoccupied space
          do
          {
            x = roll();
            y = roll();
          } 
          while(t.occupied(x,y));
          // Make a move
        }
      }
      while(!t.move(x,y));
      // Successful move!
      // Loop until finished!
    }
    // Game is finished.  Who won?
    t.printResult();
    t.printBoard();
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
