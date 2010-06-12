#ifndef POKER_HAND
#define POKER_HAND

#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>

// Boost
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

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

  // getSuit
  // Returns the suit of the card.
  Suit::Enum getSuit() const
  {
    // Suits are assigned to multiples of 13
    // Do some integer truncation magic to get the suit out
    // Since we're truncating, we get the floor of the value / 13
    return static_cast<Suit::Enum>(this->value / 13 * 13);
  }

  // getCardRank
  // Returns the suit of the card.
  CardRank::Enum getCardRank() const
  {
    // Suits are assigned to multiples of 13
    // Do some integer truncation magic to get the suit out
    // Since we're truncating, we get the floor of the value / 13
    return static_cast<CardRank::Enum>(this->value % 13);
  }

  // getValue
  // Returns the integer value of the card.
  uint8_t getValue() const
  {
    return this->value;
  }

  // Inequality
  // Simply call equality
  bool operator != (const Card& card) const
  {
    return not (*this == card);
  }

  // Equality
  // Only consider numeric values
  // value % 13 erases suits.
  bool operator == (const Card& card) const
  {
    return (this->value % 13) == (card.value % 13);
  }

  // Greater Than
  // Simply call less than.
  bool operator > (const Card& card) const
  {
    return card < *this;
  }

  // Less Than
  // Only consider numeric values
  // value % 13 erases suits.
  bool operator < (const Card& card) const
  {
    return (this->value % 13) < (card.value % 13);
  }

  operator uint8_t() const
  {
    return this->value;
  }

  operator std::string() const
  {
    std::string s;
    // Execute switch for the card
    switch(static_cast<uint8_t>(*this) % 13)
    {
      case CardRank::TWO:
        s += "2";
        break;
      case CardRank::THREE:
        s += "3";
        break;
      case CardRank::FOUR:
        s += "4";
        break;
      case CardRank::FIVE:
        s += "5";
        break;
      case CardRank::SIX:
        s += "6";
        break;
      case CardRank::SEVEN:
        s += "7";
        break;
      case CardRank::EIGHT:
        s += "8";
        break;
      case CardRank::NINE:
        s += "9";
        break;
      case CardRank::TEN:
        s += "10";
        break;
      case CardRank::JACK:
        s += "J";
        break;
      case CardRank::QUEEN:
        s += "Q";
        break;
      case CardRank::KING:
        s += "K";
        break;
      case CardRank::ACE:
        s += "A";
        break;
      default:
        s += "?";
        break;
    }
    // Execute switch for the suit
    switch(getSuit())
    {
      case Suit::SPADES:
        s += "S";
        break;
      case Suit::HEARTS:
        s += "H";
        break;
      case Suit::DIAMONDS:
        s += "D";
        break;
      case Suit::CLUBS:
        s += "C";
        break;
      default:
        s += "?";
        //s += boost::lexical_cast<std::string>(getValue() / 13);
        break;
    }
    return s;
  }

  // Precedes
  // Checks to see if this card comes right before the next
  // with regard to numeric value.
  bool precedes(Card& card)
  {
    return (this->value % 13) == (static_cast<uint8_t>(card.value % 13)) - 1;
  }
private:
  // Each card is just an unsigned integer from 0 to 51.
  uint8_t value;
};

class PokerHand
{
public:

  // Boost.Array constructor
  // The Boost Array template parameters guarantee the size.
  // Misuse will result in a compile error.
  PokerHand(boost::array<Card, 5>& array)
  {
    boost::array<Card, 5>::const_iterator array_iter = array.begin();
    uint8_t i = 0;
    while(array_iter != array.end())
    {
      this->cards[i] = *array_iter;
      ++i;
      ++array_iter;
    }
    // Sort our hand so we can calculate its rank
    // Use binary predicate to just sort on CardValue and not Suit
    std::sort(this->cards, this->cards + 5);
    // Since we're sorted, the high card is at the end.
    // Calculate the rank of our hand
    calculateRank();
  }

  // Initialize a new poker hand with 5 cards
  PokerHand(Card& card1, Card& card2, Card& card3, Card& card4, Card& card5)
  {
    this->cards[0] = card1;
    this->cards[1] = card2;
    this->cards[2] = card3;
    this->cards[3] = card4;
    this->cards[4] = card5;
    // Sort our hand so we can calculate its rank
    // Use binary predicate to just sort on CardValue and not Suit
    std::sort(this->cards, this->cards + 5);
    // Since we're sorted, the high card is at the end.
    // Calculate the rank of our hand
    calculateRank();
  }
  bool operator > (PokerHand& otherHand);
  bool operator >= (PokerHand& otherHand);
  bool operator < (PokerHand& otherHand);
  bool operator <= (PokerHand& otherHand);

  bool operator == (PokerHand& otherHand)
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

  // Use the getCard routine to get the last card.
  void setRank(const HandRanking::Enum& rank) 
  {
    this->rank = rank;
  }

  // Use the getCard routine to get the last card.
  const HandRanking::Enum getRank() const
  {
    return this->rank;
  }

  // Use the getCard routine to get the last card.
  const Card& getHighCard() const
  {
    return getCard(numCards - 1);
  }

  // Simply return the requested card
  const Card& getCard(uint8_t index) const
  {
    return this->cards[index];
  }

  operator std::string()
  {
    string s;
    // For all but the last card
    int i;
    for(i = 0; i < numCards - 1; i++)
    {
      s += (std::string)getCard(i) + " ";
    }
    // Now i == numCards - 1
    s += (std::string)getCard(i);
    return s;
  }

private:
  // Calculates the hand rank based on the cards in hand.
  // Simply calls the ranking methods in order.
  void calculateRank()
  {
    checkPairs();
    checkStraight();
    checkFlush();
  }

  // Flush
  // See if we have 5 of a given suit.
  // Possible outcomes: STRAIGHT, STRAIGHT FLUSH
  void checkFlush()
  {
    bool failed = false;
    for(int i = 1; i < numCards; i++)
    {
      // Compare this card to the next.
      if(this->cards[0].getSuit() != this->cards[i].getSuit())
      {
        // We've failed to make a straight.
        failed = true;
        break;
      }
    }
    if(!failed)
    {
      // We have a flush.  I wonder if it's a straight flush!
      // Since we called checkStraight before this, we can tell.
      if(HandRanking::STRAIGHT == this->rank)
      {
        // Indeed, we have a straight flush.
        this->rank = HandRanking::STRAIGHT_FLUSH;
      }
      // Make sure we don't have four-of-a-kind or a full house.
      else if(HandRanking::FOUR_OF_A_KIND != this->rank ||
              HandRanking::FULL_HOUSE     != this->rank
             )
      {
        // Too bad we don't have those hands.  Set to flush.
        this->rank = HandRanking::FLUSH;
      }
      
    }
  }

  // Straight
  // Just compare numeric value of this card to the next
  // Use equality operator, which compares just values
  // If it's always increasing by one, we've got a straight.
  // Possible outcomes: STRAIGHT
  void checkStraight()
  {
    uint8_t inARow = 1; // Number of cards we've seen in a row
    for(int i = 0; i < numCards - 1; i++)
    {
      // Compare this card to the next.
      if(this->cards[i].precedes(this->cards[i + 1]))
      {
        // We've found another one in order
        ++inARow;
      }
    }
    // If all 4 comparisons succeed, we have a straight
    if(5 == inARow)
    {
      this->rank = HandRanking::STRAIGHT;
    }
  }

  // Pair
  // Just compare numeric value of this card to the next
  // Use equality operator, which compares just values
  // Possible outcomes: HIGH_CARD, PAIR, THREE_OF_A_KIND,
  //   TWO_PAIR, FOUR_OF_A_KIND, FULL_HOUSE
  void checkPairs()
  {
    int i = 0;
    const Card* card = &getCard(i);
    while(i < numCards - 1)
    {
      // Set j to index of next card
      int numAlike;
      card = &getCard(i);
      int j = i + 1;
      // Find how many alike cards follow
      while(j < numCards && *card == getCard(j))
      {
        ++j;
      }
      // The distance from our original value of j is the number of alike
      // cards.
      numAlike = j - (i + 1);
      //cout << "Number of alike: " << numAlike << endl;

      // Calculate Hand Rank
      switch(numAlike)
      {
        case 0: // None
          // Do nothing.
          break;
        case 1: // Pair
          if(HandRanking::PAIR == getRank())
          {
            // We already have a pair!  2 pair now.
            setRank(HandRanking::TWO_PAIR);
          }
          else
          {
            // Otherwise, just set one pair.
            setRank(HandRanking::PAIR);
          }
          break;
        case 2: // Three of a kind
          if(HandRanking::PAIR == getRank())
          {
            // We already have a pair!  Full House
            setRank(HandRanking::FULL_HOUSE);
          }
          else
          {
            // Otherwise, just set three of a kind.
            setRank(HandRanking::THREE_OF_A_KIND);
          }
          break;
        case 3: // Four of a kind
          // Can't be combined with anything.
          setRank(HandRanking::FOUR_OF_A_KIND);
          break;
        default:
          // Should never hit this state with a valid hand.
          break;
      }
      // Set i to j.
      i = j;
    }
  }
  // We've got 5 cards
  static const uint8_t numCards = 5;
                     
  HandRanking::Enum rank; // Holds the rank of the hand
  uint8_t rank_high_index; // Holds the index of the high card for the rank.
  Card cards[numCards]; // Holds cards for the hand
};
// Inlines
#endif // POKER_HAND
