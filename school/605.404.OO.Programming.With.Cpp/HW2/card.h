#ifndef CARD_H
#define CARD_H
#include <iostream>
using std::cout;
using std::endl;
#include <stdint.h>
#include <string>
using std::string;

// The actual numeric values for the cards
namespace CardRank
{
  enum Enum
  {
    TWO, THREE, FOUR, FIVE, SIX,
    SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
  };
}

// Suit
// Set for arithmetic operations
namespace Suit
{
  enum Enum
  {
    SPADES = 0,
    HEARTS = 13,
    DIAMONDS = 26,
    CLUBS = 39
  };
}

class Card
{
public:

  // Default constructor
  Card()
    : value(0)
  {
    // Empty
    // Default is the 2 of spades (0)
  }
  // Sets card to a value, usually using enums CardRanks and Suits
  // The sum of the Suit and the CardRank is our value
  Card(uint8_t value)
  {
    this->value = value;
  }

  // Alternative 2-param constructor does the addition for you.
  Card(uint8_t value, uint8_t suit)
  {
    this->value = value + suit;
  }

  // Copy Constructor
  Card(Card& card)
  {
    this->value = card.value;
  }

  // Precedes
  // Checks to see if this card comes right before the next
  // with regard to numeric value.
  bool precedes(Card& card) const;
  // getSuit
  // Returns the suit of the card.
  Suit::Enum getSuit() const;
  // getCardRank
  // Returns the suit of the card.
  CardRank::Enum getCardRank() const;
  // getValue
  // Returns the integer value of the card.
  uint8_t getValue() const;
  // Inequality
  // Simply call equality
  bool operator != (const Card& card) const;
  // Equality
  bool operator == (const Card& card) const;
  // Greater Than
  // Simply call less than.
  bool operator > (const Card& card) const;
  // Less Than
  bool operator < (const Card& card) const;
  // uint8_t cast overload
  operator uint8_t() const;
  // string cast overload
  operator string() const;

private:
  // Each card is just an unsigned integer from 0 to 51.
  uint8_t value;
};
// Inlines

// getSuit
inline Suit::Enum Card::getSuit() const
{
  // Suits are assigned to multiples of 13
  // Do some integer truncation magic to get the suit out
  // Since we're truncating, we get the floor of the value / 13
  return static_cast<Suit::Enum>(this->value / 13 * 13);
}

// getCardRank
inline CardRank::Enum Card::getCardRank() const
{
  // Suits are assigned to multiples of 13
  // Do some integer truncation magic to get the suit out
  // Since we're truncating, we get the floor of the value / 13
  return static_cast<CardRank::Enum>(this->value % 13);
}

// getValue
inline uint8_t Card::getValue() const
{
  return this->value;
}

// Inequality
// Only consider numeric values
// value % 13 erases suits.
inline bool Card::operator != (const Card& card) const
{
  return not (*this == card);
}

// Equality
inline bool Card::operator == (const Card& card) const
{
  return (this->value % 13) == (card.value % 13);
}

// Greater Than
inline bool Card::operator > (const Card& card) const
{
  return card < *this;
}
// Less Than
// Only consider numeric values
// value % 13 erases suits.
inline bool Card::operator < (const Card& card) const
{
  return (this->value % 13) < (card.value % 13);
}

inline Card::operator uint8_t() const
{
  return this->value;
}

// Precedes
inline bool Card::precedes(Card& card) const
{
  if ( ((this->value + 1) % 13) == (card.value % 13) )
  {
    // Normal success.  Card value is one more.
    return true;
  }
  // Otherwise, return false indicating no precession
  return false;
}
#endif // CARD_H
