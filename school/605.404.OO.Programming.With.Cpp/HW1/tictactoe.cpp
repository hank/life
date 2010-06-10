// TicTacToe implementation
// Implements functions of the TicTacToe class.
#include <iostream>
#include <string>
using std::string;
#include "tictactoe.h"

// Default Constructor
//   Initializes a fresh game for us.
TicTacToe::TicTacToe()
{
  // Start with a freshly cleared board
  clearBoard();
}

// Destructor
//   Currently does nothing.
TicTacToe::~TicTacToe()
{
  // Destructor is blank.
}

// clearBoard
//   Clears the board
//   Sets all the board spaces the the space character.
//   Resets the winner to 0
//   Sets the starting player to X
//   Resets move counter and finished flag
void TicTacToe::clearBoard()
{
  // Clear board
  for(uint8_t i = 1; i <= 3; i++)
  {
    for(uint8_t j = 1; j <= 3; j++)
    {
      setBoard(i, j, ' ');
    }
  }
  // Clear winner
  winner = '\0';
  // Player 1 always starts
  current_player = 'X';
  // Reset move counter
  moves = 0;
  finflag = false;
}

// isInBounds
// Checks to see if the given offsets are inside the board
// Must be used for safety before dereferencing sections of the board.
bool TicTacToe::isInBounds(uint8_t x, uint8_t y) const
{
  // Check bounds
  if(x == 0 || y == 0 || x > 3 || y > 3)
  {
    return false;
  }
  return true;
}

// Occupied
// Finds if a given space is occupied on the board.
bool TicTacToe::occupied(uint8_t x, uint8_t y) const
{
  if(!isInBounds(x, y)) return false;
  // If that succeeds, check the space.
  return (' ' != getBoard(x, y));
}

// Move
// Returns true if move was successful
// Returns false if move was invalid - out of bounds or occupied
bool TicTacToe::move(uint8_t x, uint8_t y)
{
  // Check bounds
  if(!isInBounds(x, y)) return false;

  // Check current state of board space
  if(occupied(x, y)) 
  {
    // If already occupied, get out
    // Do not increment move counter
    return false;
  }
  // Set the space as owned by X or O
  setBoard(x, y, current_player);
  // Increment move counter
  setMoves(this->moves + 1);
  return true;
}

bool TicTacToe::finished()
{
  // Maybe we've already set the finished flag
  if(true == getFinFlag()) return true;

  // Check to see if board is a win
  // Check rows
  for(uint8_t i = 1; i <= 3; i++) {
    if(' ' != getBoard(i, 1) && 
              getBoard(i, 1) == getBoard(i, 2) &&
              getBoard(i, 1) == getBoard(i, 3)
      )
    {
      // Row is a win!
      setWinner(getBoard(i, 1));
    }
  }
  // Check columns
  for(uint8_t i = 1; i <= 3; i++) {
    if(' ' != getBoard(1, i) &&
              getBoard(1, i) == getBoard(2, i) && 
              getBoard(1, i) == getBoard(3, i)
      )
    {
      // Column is a win!
      setWinner(getBoard(1, i));
    }
  }
  // Check cross
  if(' ' != getBoard(2, 2) &&
      ( (getBoard(1, 1) == getBoard(2, 2) && getBoard(2, 2) == getBoard(3, 3)) ||
        (getBoard(1, 3) == getBoard(2, 2) && getBoard(2, 2) == getBoard(3, 1))
      )
    )
  {
    // Cross is a win!
    setWinner(getBoard(2, 2));
  }

  // Check for a tie
  if(9 == getMoves()) {
    setFinished(true);
  }

  // Return true only if we've finished
  return getFinFlag();
}

// printResult()
//   Prints a one-line result of the current game.
//   Not const because it calls finished()
void TicTacToe::printResult()
{
  // Make sure game is finished
  if(!finished())
  {
    std::cout << "The game is not finished.  It's " << getCurrentPlayer() << "'s move.\n";
  }
  else
  {
    if(getWinner()) 
    {
      std::cout << "The winner is " << getWinner() << "!\n";
    }
    else
    {
      std::cout << "Game was a tie!\n";
    }
  }
}

// printBoard()
//   Prints the board to the screen in a nice square layout
void TicTacToe::printBoard() const
{
  std::cout << "   1 2 3" << std::endl;
  for(int i = 1; i <= 3; i++)
  {
    std::cout << i << " |";
    for(int j = 1; j <= 3; j++)
    {
      std::cout << getBoard(i, j) << "|";
    }
    std::cout << "\n";
  }
}

// getStringBoard()
//   Used for unit testing purposes
//   Converts the board array to a std::string
const string TicTacToe::getStringBoard() const
{
  string s; 
  for(int i = 1; i <= 3; i++)
  {
    for(int j = 1; j <= 3; j++)
    {
      s += getBoard(i, j);
    }
  }
  return s;
}
