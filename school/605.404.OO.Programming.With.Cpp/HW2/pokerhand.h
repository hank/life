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
namespace HandRank
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

  bool operator > (const PokerHand& otherHand) const;
  bool operator >= (const PokerHand& otherHand) const;
  bool operator < (const PokerHand& otherHand) const;
  bool operator <= (const PokerHand& otherHand) const;
  bool operator == (const PokerHand& otherHand) const;
  bool operator != (const PokerHand& otherHand) const;

  // getHandRank returns the current rank of the hand
  const HandRank::Enum getHandRank() const;
  // getHighCard returns the current overall high card
  const Card& getHighCard() const;
  // getFirstRank returns the high card for the first rank
  const CardRank::Enum getFirstRank() const;
  // getSecondRankHighCard returns the high card for the second rank
  const CardRank::Enum getSecondRank() const;
  // Simply return the requested card
  const Card& getCard(uint8_t index) const;
  // Simply return a writable version of the card
  Card& getCard(uint8_t index);
  // String cast operator
  operator string();

private:
  // Set the rank of the hand to a specific value
  void setHandRank(const HandRank::Enum& rank);
  // Set the rank of the first part
  void setFirstRank(const Card& card);
  // Set the rank of the second part, if necessary.
  void setSecondRank(const Card& card);
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
  // Compare
  // Compares with another hand and returns a result indicating
  // which is superior.
  int8_t compare(const PokerHand& otherHand) const;
  
  static const uint8_t numCards = 5; // We've got 5 cards
  HandRank::Enum handRank; // Holds the rank of the hand
  CardRank::Enum firstRank; // Holds the first rank
  CardRank::Enum secondRank; // Holds the second rank
  Card cards[numCards]; // Holds cards for the hand
};

// setHandRank
inline void PokerHand::setHandRank(const HandRank::Enum& handRank) 
{
  this->handRank = handRank;
}

// setFirstRank
inline void PokerHand::setFirstRank(const Card& card) 
{
  this->firstRank = card.getCardRank();
}

// setSecondRank
inline void PokerHand::setSecondRank(const Card& card) 
{
  this->secondRank = card.getCardRank();
}

// getRank
inline const HandRank::Enum PokerHand::getHandRank() const
{
  return this->handRank;
}

// getFirstRank
inline const CardRank::Enum PokerHand::getFirstRank() const
{
  return this->firstRank;
}

// getSecondRank
inline const CardRank::Enum PokerHand::getSecondRank() const
{
  return this->secondRank;
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

// calculateRank
inline void PokerHand::calculateRank()
{
  checkPairs();
  checkStraight();
  checkFlush();
}
#endif // POKER_HAND
