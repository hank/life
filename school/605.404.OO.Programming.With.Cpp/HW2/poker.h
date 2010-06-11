#ifndef POKER_HAND
#define POKER_HAND

#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>

// CardValues
enum CardValues
{
  TWO, THREE, FOUR, FIVE, SIX,
  SEVEN, EIGHT, NINE, TEN,
  JACK, QUEEN, KING, ACE
};

// Suits
// Set for arithmetic operations
enum Suits
{
  SPADES = 0,
  HEARTS = 13,
  DIAMONDS = 26,
  CLUBS = 39
};

class Card
{
public:

  // Default constructor
  Card()
  {
    // Empty
  }
  // Sets card to a value, usually using enums CardValues and Suits
  // The sum of the Suit and the CardValue is our value
  Card(uint8_t value)
  {
    this->value = value;
  }

  Card(uint8_t value, uint8_t suit)
  {
    this->value = value + suit;
  }

  // Copy Constructor
  Card(Card& card)
  {
    this->value = card.value;
  }

  bool operator < (const Card& card) const
  {
    return this->value < card.value;
  }

  operator int() const
  {
    return this->value;
  }

  operator std::string()
  {
    std::string s;
    // Execute switch for the card
    switch(static_cast<int>(*this) % 13)
    {
      case TWO:
        s += "2";
        break;
      case THREE:
        s += "3";
        break;
      case FOUR:
        s += "4";
        break;
      case FIVE:
        s += "5";
        break;
      case SIX:
        s += "6";
        break;
      case SEVEN:
        s += "7";
        break;
      case EIGHT:
        s += "8";
        break;
      case NINE:
        s += "9";
        break;
      case TEN:
        s += "10";
        break;
      case JACK:
        s += "J";
        break;
      case QUEEN:
        s += "Q";
        break;
      case KING:
        s += "K";
        break;
      case ACE:
        s += "A";
        break;
      default:
        s += "?";
        break;
    }
    // Execute switch for the suit
    switch(static_cast<int>(*this) / 13)
    {
      case 0: // SPADES
        s += "S ";
        break;
      case 1: // HEARTS
        s += "H ";
        break;
      case 2: // DIAMONDS
        s += "D ";
        break;
      case 3: // CLUBS
        s += "C ";
        break;
      default:
        s += "? ";
        break;
    }
    return s;
  }
private:
  // Each card is just an unsigned integer from 0 to 51.
  int value;
};

class PokerHand
{
public:
  // Hand ranks, in order of awesomeness.
  enum HandRanking
  {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
  };
  // Initialize a new poker hand with 5 cards
  PokerHand(Card& card1, Card& card2, Card& card3, Card& card4, Card& card5)
  {
    this->cards[0] = card1;
    this->cards[1] = card2;
    this->cards[2] = card3;
    this->cards[3] = card4;
    this->cards[4] = card5;
    // Sort our hand so we can calculate its rank
    std::sort(this->cards, this->cards + 5);
    // Calculate the rank of our hand
    calculateRank();
  }
  bool operator > (PokerHand& otherHand);
  bool operator >= (PokerHand& otherHand);
  bool operator < (PokerHand& otherHand);
  bool operator <= (PokerHand& otherHand);
  bool operator == (PokerHand& otherHand);

  operator std::string()
  {
    string s;
    for(int i = 0; i < numCards; i++)
    {
      s += (std::string)(cards[i]);
    }
    return s;
  }

private:
  // Calculates the hand rank based on the cards in hand.
  void calculateRank()
  {
    // Pair
    for(int i = 0; i < numCards - 1; i++)
    {
    }
  }
  // We've got 5 cards
  static const uint8_t numCards = 5;
                     
  HandRanking rank; // Holds the rank of the hand
  Card cards[numCards]; // Holds cards for the hand
  uint8_t highCardIndex; // Index of the high card
};
// Inlines
#endif // POKER_HAND
