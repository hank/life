#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <exception>

// BOOST Random headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

class TicTacToe
{
  public:
    TicTacToe()
    {
      // Start with a freshly cleared board
      clear();
    }

    ~TicTacToe()
    {
    }

    void clear()
    {
      // Clear board
      for(uint8_t i = 0; i < 3; i++)
      {
        for(uint8_t j = 0; j < 3; j++)
        {
          board[i][j] = 0;
        }
      }
      // Clear winner
      winner = 0;
      // Player 1 always starts
      current_player = 1;
      // Reset move counter
      moves = 0;
    }

    uint8_t get_current_player()
    {
      return current_player;
    }

    uint8_t get_winner()
    {
      return winner;
    }

    void move(uint8_t x, uint8_t y)
    {
      // Check current state of board space
      if(0 != board[x][y]) 
      {
        // If already occupied, get out
        // Specifically do not increment move counter
        return;
      }
      // Set the space as owned by X or O
      printf("Player %u @ (%u, %u)\n", current_player, x, y);
      board[x][y] = current_player;
      // Increment move counter
      moves++;
    }

    void change_player()
    {
      // Change current player to other player
      // b01 and b10 are the player numbers
      // XOR with b11 to swap.
      current_player ^= 3;
    }

    bool finished()
    {
      // Check to see if board is a win
      // Check rows
      for(uint8_t i = 0; i < 2; i++) {
        if(board[i][0] != 0 &&
           board[i][0] == board[i][1] &&
           board[i][0] == board[i][2]
          )
        {
          // Row is a win!
          winner = board[i][0];
          return true;
        }
      }
      // Check columns
      for(uint8_t i = 0; i < 2; i++) {
        if(board[0][i] != 0 &&
           board[0][i] == board[1][i] &&
           board[0][i] == board[2][i]
          )
        {
          // Column is a win!
          winner = board[0][i];
          return true;
        }
      }
      // Check cross
      if(board[1][1] != 0 &&
         (
           (board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
           (board[0][2] == board[1][1] && board[1][1] == board[2][0])
         )
        )
      {
        // Cross is a win!
        winner = board[1][1];
        return true;
      }

      // Check for a tie
      if(moves == 9) {
        return true;
      }

      // Otherwise, no win yet.
      return false;
    }

    void print_result()
    {
      if(winner) 
      {
        printf("The winner is Player %u!\n", winner);
      }
      else
      {
        printf("Game was a tie!\n");
      }
    }

    void print_board()
    {
      for(int i = 0; i < 3; i++)
      {
        printf("|");
        for(int j = 0; j < 3; j++)
        {
          printf("%u|", board[i][j]);
        }
        printf("\n");
      }
    }

  private:
    uint8_t board[3][3];
    uint8_t current_player;
    uint8_t winner;
    uint8_t moves;
};

int main()
{
  TicTacToe t;
  uint8_t x, y;
  char c;

  // BOOST Random generation support
  boost::mt19937 gen;
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
      printf("%u, %u\n", x, y);
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
