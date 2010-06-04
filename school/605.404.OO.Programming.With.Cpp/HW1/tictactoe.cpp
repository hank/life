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
      board[i][j] = ' ';
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

char TicTacToe::getCurrentPlayer()
{
  return current_player;
}

char TicTacToe::getWinner()
{
  return winner;
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
  if(' ' != board[x - 1][y - 1]) 
  {
    // If already occupied, get out
    // Do not increment move counter
    std::cout << "Space was already occupied by " << board[x - 1][y - 1] << 
      " Try again.\n";
    return false;
  }
  // Set the space as owned by X or O
  board[x - 1][y - 1] = current_player;
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
    if(board[i][0] != ' ' &&
        board[i][0] == board[i][1] &&
        board[i][0] == board[i][2]
      )
    {
      // Row is a win!
      winner = board[i][0];
      finflag = 1;
      return true;
    }
  }
  // Check columns
  for(uint8_t i = 0; i < 2; i++) {
    if(board[0][i] != ' ' &&
        board[0][i] == board[1][i] &&
        board[0][i] == board[2][i]
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
       (board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
       (board[0][2] == board[1][1] && board[1][1] == board[2][0])
      )
    )
  {
    // Cross is a win!
    winner = board[1][1];
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

void TicTacToe::printResult()
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

void TicTacToe::printBoard()
{
  std::cout << "   1 2 3" << std::endl;
  for(int i = 0; i < 3; i++)
  {
    std::cout << i+1 << " |";
    for(int j = 0; j < 3; j++)
    {
      std::cout << board[i][j] << "|";
    }
    std::cout << "\n";
  }
}

const string TicTacToe::getBoard()
{
  string s; 
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      s += board[i][j];
    }
  }
  return s;
}
