#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include "tictactoe.cpp"

int main()
{
  TicTacToe t;
  // Movement variables
  unsigned int x, y;
  std::stringstream ss;
  std::string input;

  while(1) {
    // Until we finish a game
    std::cout << "To move, put row (1-3) then column (1-3) like so: 1 3" << std::endl;
    std::cout << "Then press Enter." << std::endl;
    while(false == t.finished()) 
    {
      t.print_board();
      do 
      {
        std::cout << t.get_current_player() << "'s move: ";
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
            break;
          }
          else
          {
            // Bad input
            std::cout << "Bad input.  Try again." << std::endl;
            std::cout << t.get_current_player() << "'s move: ";
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
      while(!t.move(x,y));
      // Successful move!
      // Change the active player
      t.change_player();
    }
    // Game is finished.  Who won?
    t.print_result();
    t.print_board();
    // Continue?
    std::cout << "Press Enter to play again!\n";
    // Get a single character from the keyboard
    // If it's not a newline, break out of the while loop
    if(std::cin.get() != '\n') break;
    // Otherwise, clear the board and continue to the next game
    t.clear();
  }
  return EXIT_SUCCESS;
}
