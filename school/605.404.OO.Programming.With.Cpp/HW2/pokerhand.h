#ifndef POKER_HAND
#define POKER_HAND

#include <iostream>
#include <string>
using std::string;
#include <algorithm>
#include <stdint.h>
#include "card.h"

// Boost
#include <boost/array.hpp>

// Hand ranks, in order of awesomeness.
namespace HandRanking
{
  enum Enum
  {
    HIGH_CARD = 0,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
  };
}

class PokerHand
{
public:

  // Boost.Array constructor
  // The Boost Array template parameters guarantee the size.
  // Misuse will result in a compile error.
  PokerHand(boost::array<Card, 5>& array);

  // 5 Card param constructor
  PokerHand(Card& card1, Card& card2, Card& card3, 
            Card& card4, Card& card5);

  bool operator > (PokerHand& otherHand);
  bool operator >= (PokerHand& otherHand);
  bool operator < (PokerHand& otherHand);
  bool operator <= (PokerHand& otherHand);
  bool operator == (PokerHand& otherHand);

  // Set the rank of the hand to a specific value
  void setRank(const HandRanking::Enum& rank);
  // getRank returns the current rank of the hand
  const HandRanking::Enum getRank() const;
  // getHighCard returns the current overall high card
  const Card& getHighCard() const;
  // Simply return the requested card
  const Card& getCard(uint8_t index) const;
  // Simply return a writable version of the card
  Card& getCard(uint8_t index);
  // String cast operator
  operator string();

private:
  // Calculates the hand rank based on the cards in hand.
  // Simply calls the ranking methods in order.
  void calculateRank();
  // Flush
  // See if we have 5 of a given suit.
  // Possible outcomes: STRAIGHT, STRAIGHT FLUSH
  void checkFlush();
  // Straight
  // Just compare numeric value of this card to the next
  // Use equality operator, which compares just values
  // If it's always increasing by one, we've got a straight.
  // Possible outcomes: STRAIGHT
  void checkStraight();
  // Pair
  // Just compare numeric value of this card to the next
  // Use equality operator, which compares just values
  // Possible outcomes: HIGH_CARD, PAIR, THREE_OF_A_KIND,
  //   TWO_PAIR, FOUR_OF_A_KIND, FULL_HOUSE
  void checkPairs();
  
  static const uint8_t numCards = 5; // We've got 5 cards
  HandRanking::Enum rank; // Holds the rank of the hand
  uint8_t rank_high_index; // Holds the index of the high card for the rank.
  Card cards[numCards]; // Holds cards for the hand
};

// Equality
inline bool PokerHand::operator == (PokerHand& otherHand)
{
  for(int i = 0; i < numCards; ++i)
  {
    if(getCard(i) != otherHand.getCard(i))
    {
      return false;
    }
  }
  // All comparisons succeeded
  return true;
}

// setRank
inline void PokerHand::setRank(const HandRanking::Enum& rank) 
{
  this->rank = rank;
}

// getRank
inline const HandRanking::Enum PokerHand::getRank() const
{
  return this->rank;
}

// getHighCard
inline const Card& PokerHand::getHighCard() const
{
  return getCard(numCards - 1);
}

// getCard (const)
inline const Card& PokerHand::getCard(uint8_t index) const
{
  return this->cards[index];
}

// getCard
inline Card& PokerHand::getCard(uint8_t index)
{
  return this->cards[index];
}

inline void PokerHand::calculateRank()
{
  checkPairs();
  checkStraight();
  checkFlush();
}
#endif // POKER_HAND
