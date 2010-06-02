#include <stdio.h>
class TicTacToe
{
  public:
    TicTacToe();
    ~TicTacToe();

    // Sets the board to an initial condition
    void clear();

    // Returns the current player
    char get_current_player();
    // Returns the game winner, or 0 if there is none.
    char get_winner();
    // Executes a move by the current player
    // Increments the move counter for the current game
    void move(uint8_t x, uint8_t y);
    // Changes the current player to the other player
    void change_player();
    // Checks to see if the game is in a finished state (win/tie)
    // Returns true when game is over, sets winner, sets finished flag.
    // Returns false if game needs to continue.
    bool finished();
    // Prints the result of a finished game.
    void print_result();
    // Prints the current state of the board
    void print_board();

  private:
    char board[3][3];
    char current_player;
    char winner;
    uint8_t moves;
    bool finflag;
};
