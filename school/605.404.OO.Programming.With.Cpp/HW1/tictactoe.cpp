#include "tictactoe.h"
TicTacToe::TicTacToe()
{
  // Start with a freshly cleared board
  clear();
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::clear()
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

char TicTacToe::get_current_player()
{
  return current_player;
}

char TicTacToe::get_winner()
{
  return winner;
}

void TicTacToe::move(uint8_t x, uint8_t y)
{
  printf("%c @ (%u, %u)\n", current_player, x, y);
  // Check current state of board space
  if(' ' != board[x][y]) 
  {
    // If already occupied, get out
    // Do not increment move counter
    printf("Space was already occupied by %c.  Try again.\n", board[x][y]);
    return;
  }
  // Set the space as owned by X or O
  board[x][y] = current_player;
  // Increment move counter
  moves++;
}

void TicTacToe::change_player()
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

void TicTacToe::print_result()
{
  // Make sure game is finished
  if(!finflag)
  {
    printf("The game is not finished.  It's %c's move.", current_player);
  }
  else
  {
    if(winner) 
    {
      printf("The winner is %c!\n", winner);
    }
    else
    {
      printf("Game was a tie!\n");
    }
  }
}

void TicTacToe::print_board()
{
  for(int i = 0; i < 3; i++)
  {
    printf("|");
    for(int j = 0; j < 3; j++)
    {
      printf("%c|", board[i][j]);
    }
    printf("\n");
  }
}
