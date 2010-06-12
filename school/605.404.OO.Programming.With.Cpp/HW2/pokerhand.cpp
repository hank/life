#include <string>
using std::string;
#include "card.h"
#include "pokerhand.h"
// Boost.Array constructor
PokerHand::PokerHand(boost::array<Card, 5>& array)
{
  boost::array<Card, 5>::const_iterator array_iter = array.begin();
  uint8_t i = 0;
  while(array_iter != array.end())
  {
    getCard(i) = *array_iter;
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
PokerHand::PokerHand(Card& card1, Card& card2, Card& card3, 
                     Card& card4, Card& card5)
{
  getCard(0) = card1;
  getCard(1) = card2;
  getCard(2) = card3;
  getCard(3) = card4;
  getCard(4) = card5;
  // Sort our hand so we can calculate its rank
  // Use binary predicate to just sort on CardValue and not Suit
  std::sort(this->cards, this->cards + 5);
  // Since we're sorted, the high card is at the end.
  // Calculate the rank of our hand
  calculateRank();
}

PokerHand::operator string()
{
  string s;
  // For all but the last card
  int i;
  for(i = 0; i < numCards - 1; i++)
  {
    s += static_cast<string>(getCard(i)) + " ";
  }
  // Now i == numCards - 1
  s += static_cast<string>(getCard(i));
  return s;
}

void PokerHand::checkFlush()
{
  bool failed = false;
  for(int i = 1; i < numCards; i++)
  {
    // Compare this card to the next.
    if(getCard(0).getSuit() != getCard(i).getSuit())
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
    if(HandRanking::STRAIGHT == getRank())
    {
      // Indeed, we have a straight flush.
      setRank(HandRanking::STRAIGHT_FLUSH);
    }
    // Make sure we don't have four-of-a-kind or a full house.
    else if(HandRanking::FOUR_OF_A_KIND != getRank() ||
            HandRanking::FULL_HOUSE     != getRank()
           )
    {
      // Too bad we don't have those hands.  Set to flush.
      setRank(HandRanking::FLUSH);
    }
    
  }
}

void PokerHand::checkStraight()
{
  uint8_t inARow = 1; // Number of cards we've seen in a row
  for(int i = 0; i < numCards - 1; i++)
  {
    // Compare this card to the next.
    if(getCard(i).precedes(getCard(i + 1)))
    {
      // We've found another one in order
      ++inARow;
    }
  }
  // If all 4 comparisons succeed, we have a straight
  if(5 == inARow)
  {
    setRank(HandRanking::STRAIGHT);
  }
}

void PokerHand::checkPairs()
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
