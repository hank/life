// TicTacToe Class
// Provides an implementation of TicTacToe
#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <stdint.h>
#include <string>
using std::string;

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
    // Changes the current player to the other player
    void changePlayer();
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

    char board[3][3];
    char currentPlayer;
    char winner;
    uint8_t moves;
    bool finflag;
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
