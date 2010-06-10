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
  string s = t.getStringBoard();
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

TEST(TicTacToe, BoundsCheck)
{
  TicTacToe t;
  ASSERT_FALSE(t.isInBounds(10,35));
  ASSERT_FALSE(t.isInBounds(0,2));
  ASSERT_TRUE(t.isInBounds(1,3));
  ASSERT_FALSE(t.isInBounds(2,4));
}

TEST(TicTacToe, Finished)
{
  TicTacToe t;
  t.move(1, 1);
  t.move(2, 1);
  t.move(3, 1);
  ASSERT_TRUE(t.finished());
}

TEST(TicTacToe, Winner)
{
  TicTacToe t;
  t.move(1, 1);
  t.move(2, 1);
  t.move(3, 1);
  ASSERT_TRUE(t.finished());
  ASSERT_EQ(t.getWinner(), 'X');
}
