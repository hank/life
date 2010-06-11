#ifndef POKER_HAND
#define POKER_HAND

#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>

// CardValues
enum CardNumericValues
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
    : value(0)
  {
    // Empty
    // Default is the 2 of spades (0)
  }
  // Sets card to a value, usually using enums CardNumericValues and Suits
  // The sum of the Suit and the CardNumericValue is our value
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

  // Equality
  // Only consider numeric values
  // value % 13 erases suits.
  bool operator == (const Card& card) const
  {
    return (this->value % 13) == (card.value % 13);
  }

  // Less Than
  // Only consider numeric values
  // value % 13 erases suits.
  bool operator < (const Card& card) const
  {
    return (this->value % 13) < (card.value % 13);
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

  // Precedes
  // Checks to see if this card comes right before the next
  // with regard to numeric value.
  bool precedes(Card& card)
  {
    return (this->value % 13) == ((int32_t)card.value % 13) - 1;
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
    checkPairs();
    checkStraight();
    //checkFlush();
  }

  // Flush
  // See if we have 5 of a given suit.
  // Possible outcomes: STRAIGHT, STRAIGHT FLUSH
  void checkFlush()
  {
    for(int i = 1; i < numCards; i++)
    {
      // Compare this card to the next.
      if(this->cards[0].getSuit() == this->cards[i])
      {
        // We've failed to make a straight.
        ++inARow;
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
    uint8_t inARow = 0; // Number of cards we've seen in a row
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
    if(4 == inARow)
    {
      this->rank = STRAIGHT;
    }
  }

  // Pair
  // Just compare numeric value of this card to the next
  // Use equality operator, which compares just values
  // Possible outcomes: HIGH_CARD, PAIR, THREE_OF_A_KIND,
  //   TWO_PAIR, FOUR_OF_A_KIND, FULL_HOUSE
  void checkPairs()
  {
    for(int i = 0; i < numCards - 1; i++)
    {
      if(cards[i] == cards[i+1])
      {
        // We found a pair.  Check if it's 3 of a kind
        if(i + 2 < numCards - 1 && cards[i + 2] == cards[i])
        {
          // We found three-of-a-kind!  Check for four-of-a-kind.
          if(i + 3 < numCards - 1 && cards[i + 3] == cards[i])
          {
            // 4-of-a-kind!
            this->rank = FOUR_OF_A_KIND;
          }
          else
          {
            // Either there's no more cards or we didn't add to our pair.
            // If we're already ranked a pair, full house!
            if(PAIR == this->rank)
            {
              this->rank == FULL_HOUSE;
            }
            else
            {
              this->rank = THREE_OF_A_KIND;
            }
          }
        }
        else
        {
          // Either there's no more cards or we didn't add to our pair.
          // If we're already ranked a pair
          if(PAIR == this->rank)
          {
            this->rank == TWO_PAIR;
          }
          // It could be a three-of-a-kind-first full house!
          else if(THREE_OF_A_KIND == this->rank)
          {
            this->rank = FULL_HOUSE;
          }
          // Otherwise, we just have one pair
          else
          {
            this->rank = PAIR;
          }
        }
      }
    }
  }
  // We've got 5 cards
  static const uint8_t numCards = 5;
                     
  HandRanking rank; // Holds the rank of the hand
  Card cards[numCards]; // Holds cards for the hand
};
// Inlines
#endif // POKER_HAND
