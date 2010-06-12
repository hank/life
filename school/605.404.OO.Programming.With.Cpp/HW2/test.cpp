#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

// Boost
#include <boost/array.hpp>

#include "poker.h"

int main()
{
  // Initialize Seven High Straight
  Card card1 = Card(SEVEN + HEARTS);
  Card card2 = Card(SIX, HEARTS);
  Card card3 = Card(FIVE + SPADES);
  Card card4 = Card(FOUR + HEARTS);
  Card card5 = Card(THREE + HEARTS);
  PokerHand p(card1, card2, card3, card4, card5);
  cout << (std::string)p << endl;
}
