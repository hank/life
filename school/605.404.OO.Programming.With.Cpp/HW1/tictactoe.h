// tictactoe.h
// Contains the TicTacToe class and inline functions
#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <stdint.h>
#include <string>
using std::string;

// TicTacToe Class
//   Provides an implementation of the game Tic-Tac-Toe
//
//   Upon instantiation, X is given the first move.  When a valid move is
//   completed, the move method changes the player and increments the move
//   counter.  The main program then must check if the game is finished, which
//   calculates if there is a winning board and sets the finished flag and
//   winner appropriately.  If the game is finished, the main program may
//   print the board, print the winner (or a tie in the event of one), or
//   reset and play again.  If the game is not finished, another move must be
//   made.  This process is repeated until a finished board is created.
//   Functions to check bounds and find if a space is occupied are available.
//   Author: Erik Gregg
//   Date: Wed Jun 9 22:55:01 EDT 2010
//
//   Copyright (c) 2010, Erik Gregg
//   All rights reserved.
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are
//   met:
//   
//       * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//       * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//       * Neither the name of Erik Gregg nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.
//   
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
class TicTacToe
{
  public:
    // Default Constructor
    //   Initializes a fresh game for us.
    TicTacToe()
    {
      // Start with a freshly cleared board
      clearBoard();
    }

    // Destructor
    virtual ~TicTacToe()
    { // Does nothing, but it's virtual!
    }

    // Sets the board to an initial condition
    void clearBoard();
    // Executes a move by the current player
    // Increments the move counter for the current game
    bool move(uint8_t x, uint8_t y);
    // Finds if a space is currently occupied
    bool occupied(uint8_t x, uint8_t y) const;
    // Checks to see if the game is in a finished state (win/tie)
    // Returns true when game is over, sets winner, sets finished flag.
    // Returns false if game needs to continue.
    bool finished();
    // Prints the result of a finished game.
    // Not const because it calls finished, which may permute members
    void printResult();
    // Prints the current state of the board
    void printBoard() const;
    // Returns a string containing the board for testing.
    const string getStringBoard() const;
    // Returns the current number of moves
    char getMoves() const;
    // Returns the current player
    char getCurrentPlayer() const;
    // Returns the game winner, or 0 if there is none.
    char getWinner() const;
    // Finds if a space is in bounds
    bool isInBounds(uint8_t x, uint8_t y) const;

  private:
    // Changes the current player to the other player
    void changePlayer();
    // Returns the given space on the board
    // Warning: offsets must be between 1 and 3.
    char getBoard(uint8_t x, uint8_t y) const;
    // Set a place on the board to a given player
    // Warning: offsets must be between 1 and 3.
    void setBoard(uint8_t x, uint8_t y, char player);
    // Returns the finished flag - should only be called inside finished()
    bool getFinFlag() const;
    // Set the finished flag
    void setFinished(bool finished);
    // Set the number of moves
    void setMoves(uint8_t moves);
    // Set the winner - also sets the finflag to true
    void setWinner(char winner);
    // Set the winner - also sets the finflag to true
    void setCurrentPlayer(char currentPlayer);

    char    board[3][3];
    char    currentPlayer;
    char    winner;
    uint8_t moves;
    bool    finflag;
};

// Inlines

// changePlayer
//   Change current player to other player
//   ASCII X is 0x58, ASCII O is 0x4F
//   XOR with 0x17 to swap.
inline void TicTacToe::changePlayer()
{
  this->currentPlayer ^= 0x17;
}

// getCurrentPlayer
inline char TicTacToe::getCurrentPlayer() const
{
  return this->currentPlayer;
}

// getMoves
inline char TicTacToe::getMoves() const
{
  return this->moves;
}

// getWinner
inline char TicTacToe::getWinner() const
{
  return this->winner;
}

// getFinFlag
inline bool TicTacToe::getFinFlag() const
{
  return this->finflag;
}

// getBoard 
// Converts from 1-indexed to 0-indexed array subscript
// Returns value at given offset
// WARNING: MUST CHECK BOUNDS BEFORE CALLING!
inline char TicTacToe::getBoard(uint8_t x, uint8_t y) const
{
  return this->board[x - 1][y - 1];
}

// setBoard 
// Converts from 1-indexed to 0-indexed array subscript
// Sets value at given offset
// WARNING: MUST CHECK BOUNDS BEFORE CALLING!
inline void TicTacToe::setBoard(uint8_t x, uint8_t y, char player)
{
  this->board[x - 1][y - 1] = player;
}

// setMoves
inline void TicTacToe::setMoves(uint8_t moves)
{
  this->moves = moves;
}

// setWinner
inline void TicTacToe::setWinner(char winner)
{
  this->winner = winner;
  this->finflag = true;
}

// setFinished
inline void TicTacToe::setFinished(bool finished)
{
  this->finflag = finished;
}

// setCurrentPlayer
inline void TicTacToe::setCurrentPlayer(char currentPlayer)
{
  this->currentPlayer = currentPlayer;
}

#endif // TICTACTOE_H
