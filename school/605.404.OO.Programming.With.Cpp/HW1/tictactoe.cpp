#include <iostream>
#include <string>
using std::string;
#include "tictactoe.h"

TicTacToe::TicTacToe()
{
  // Start with a freshly cleared board
  clearBoard();
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::clearBoard()
{
  // Clear board
  for(uint8_t i = 0; i < 3; i++)
  {
    for(uint8_t j = 0; j < 3; j++)
    {
      this->board[i][j] = ' ';
    }
  }
  // Clear winner
  winner = '\0';
  // Player 1 always starts
  current_player = 'X';
  // Reset move counter
  moves = 0;
  finflag = 0;
}

char TicTacToe::getCurrentPlayer() const
{
  return current_player;
}

char TicTacToe::getWinner() const
{
  return winner;
}

bool TicTacToe::occupied(uint8_t x, uint8_t y) const
{
  return (' ' != this->board[x - 1][y - 1]);
}

// Move
// Returns true if move was successful
// Returns false if move was invalid - out of bounds or occupied
bool TicTacToe::move(uint8_t x, uint8_t y)
{
  //std::cout << current_player << " @ " << 
  //    (unsigned int)x << ", " << (unsigned int)y << std::endl;
  // Check bounds
  if(x == 0 || y == 0 || x > 3 || y > 3)
  {
    std::cout << "Move is out of bounds.  Try again.\n";
    return false;
  }

  // Check current state of board space
  if(occupied(x, y)) 
  {
    // If already occupied, get out
    // Do not increment move counter
    return false;
  }
  // Set the space as owned by X or O
  this->board[x - 1][y - 1] = current_player;
  // Increment move counter
  moves++;
  return true;
}

void TicTacToe::changePlayer()
{
  // Change current player to other player
  // X is 0x58, O is 0x4F
  // XOR with 0x17 to swap.
  current_player ^= 0x17;
}

bool TicTacToe::finished()
{
  // Maybe we've already set the finished flag
  if(finflag) return true;

  // Check to see if board is a win
  // Check rows
  for(uint8_t i = 0; i < 2; i++) {
    if(this->board[i][0] != ' ' &&
        this->board[i][0] == this->board[i][1] &&
        this->board[i][0] == this->board[i][2]
      )
    {
      // Row is a win!
      winner = this->board[i][0];
      finflag = 1;
      return true;
    }
  }
  // Check columns
  for(uint8_t i = 0; i < 2; i++) {
    if(this->board[0][i] != ' ' &&
        this->board[0][i] == this->board[1][i] &&
        this->board[0][i] == this->board[2][i]
      )
    {
      // Column is a win!
      winner = board[0][i];
      finflag = 1;
      return true;
    }
  }
  // Check cross
  if(board[1][1] != ' ' &&
      (
       (this->board[0][0] == this->board[1][1] && 
        this->board[1][1] == this->board[2][2]) ||

       (this->board[0][2] == this->board[1][1] && 
        this->board[1][1] == this->board[2][0])
      )
    )
  {
    // Cross is a win!
    winner = this->board[1][1];
    finflag = 1;
    return true;
  }

  // Check for a tie
  if(moves == 9) {
    finflag = 1;
    return true;
  }

  // Otherwise, no win yet.
  return false;
}

void TicTacToe::printResult() const
{
  // Make sure game is finished
  if(!finflag)
  {
    std::cout << "The game is not finished.  It's " << current_player << "'s move.\n";
  }
  else
  {
    if(winner) 
    {
      std::cout << "The winner is " << winner << "!\n";
    }
    else
    {
      std::cout << "Game was a tie!\n";
    }
  }
}

void TicTacToe::printBoard() const
{
  std::cout << "   1 2 3" << std::endl;
  for(int i = 0; i < 3; i++)
  {
    std::cout << i+1 << " |";
    for(int j = 0; j < 3; j++)
    {
      std::cout << this->board[i][j] << "|";
    }
    std::cout << "\n";
  }
}

const string TicTacToe::getBoard() const
{
  string s; 
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      s += this->board[i][j];
    }
  }
  return s;
}
