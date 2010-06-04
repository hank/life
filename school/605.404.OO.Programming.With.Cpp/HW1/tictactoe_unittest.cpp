#include <gtest/gtest.h>
#include <iostream>
#include <string>
using std::string;
using std::cout;
#include "tictactoe.cpp"

TEST(TicTacToe, Move)
{
  TicTacToe t;
  t.move(1,1);
  t.move(1,3);
  t.move(3,1);
  string s = t.getBoard();
  ASSERT_STREQ("X X   X  ", s.c_str());
}

TEST(TicTacToe, TakenSpace)
{
  TicTacToe t;
  ASSERT_TRUE(t.move(1,1));
  ASSERT_FALSE(t.move(1,1));
}

TEST(TicTacToe, ChangePlayer)
{
  TicTacToe t;
  char p = t.getCurrentPlayer();
  ASSERT_EQ('X', p);
  t.changePlayer();
  p = t.getCurrentPlayer();
  ASSERT_EQ('O', p);
}
