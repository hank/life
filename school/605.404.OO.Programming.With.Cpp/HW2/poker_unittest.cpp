#include <gtest/gtest.h>
#include <iostream>
#include <string>
using std::string;
using std::cout;
#include "poker.h"

TEST(Poker, CreateHand)
{
  Card * cards = new Card[5]; // 5 Random Cards
  for(int i = 0; i < 5; i++)
  {
    cout << cards[i];
  }
  //PokerHand t(cards);
}
