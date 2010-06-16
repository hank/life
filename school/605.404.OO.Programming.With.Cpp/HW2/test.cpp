#include <iostream>
using std::cout;
using std::endl;
#include "card.h"
#include "pokerhand.h"

bool WikiStraightFlushWin()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::SEVEN, Card::HEARTS),
         Card(Card::SIX, Card::HEARTS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::FOUR, Card::HEARTS),
         Card(Card::THREE, Card::HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::FIVE, Card::SPADES),
         Card(Card::FOUR, Card::SPADES),
         Card(Card::THREE, Card::SPADES),
         Card(Card::TWO, Card::SPADES),
         Card(Card::ACE, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   // Hand 1 beats Hand 2
   return (hand1 > hand2);
}

bool WikiStraightFlushTie()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::JACK, Card::CLUBS),
         Card(Card::TEN, Card::CLUBS),
         Card(Card::NINE, Card::CLUBS),
         Card(Card::EIGHT, Card::CLUBS),
         Card(Card::SEVEN, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::NINE, Card::DIAMONDS),
         Card(Card::EIGHT, Card::DIAMONDS),
         Card(Card::SEVEN, Card::DIAMONDS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 == hand2);
}

bool WikiFourOfAKindWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::TEN, Card::CLUBS),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::TEN, Card::SPADES),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::FIVE, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::SIX, Card::CLUBS),
         Card(Card::SIX, Card::HEARTS),
         Card(Card::SIX, Card::SPADES),
         Card(Card::SIX, Card::DIAMONDS),
         Card(Card::KING, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiFourOfAKindWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::TEN, Card::CLUBS),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::TEN, Card::SPADES),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::QUEEN, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::TEN, Card::CLUBS),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::TEN, Card::SPADES),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::FIVE, Card::DIAMONDS),
      }
   };


   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiFullHouseWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::TEN, Card::SPADES),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::FOUR, Card::SPADES),
         Card(Card::FOUR, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::NINE, Card::HEARTS),
         Card(Card::NINE, Card::CLUBS),
         Card(Card::NINE, Card::SPADES),
         Card(Card::ACE, Card::HEARTS),
         Card(Card::ACE, Card::CLUBS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiFullHouseWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::ACE, Card::SPADES),
         Card(Card::ACE, Card::CLUBS),
         Card(Card::ACE, Card::HEARTS),
         Card(Card::FOUR, Card::DIAMONDS),
         Card(Card::FOUR, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::ACE, Card::SPADES),
         Card(Card::ACE, Card::HEARTS),
         Card(Card::ACE, Card::DIAMONDS),
         Card(Card::THREE, Card::SPADES),
         Card(Card::THREE, Card::DIAMONDS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiFlushWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::ACE, Card::HEARTS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::THREE, Card::HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::KING, Card::SPADES),
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::JACK, Card::SPADES),
         Card(Card::NINE, Card::SPADES),
         Card(Card::SIX, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiFlushWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::ACE, Card::DIAMONDS),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::SEVEN, Card::DIAMONDS),
         Card(Card::SIX, Card::DIAMONDS),
         Card(Card::TWO, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::ACE, Card::HEARTS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::TEN, Card::HEARTS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::THREE, Card::HEARTS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiStraightWin()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::SEVEN, Card::SPADES),
         Card(Card::SIX, Card::HEARTS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::FOUR, Card::SPADES),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::SIX, Card::DIAMONDS),
         Card(Card::FIVE, Card::SPADES),
         Card(Card::FOUR, Card::DIAMONDS),
         Card(Card::THREE, Card::HEARTS),
         Card(Card::TWO, Card::CLUBS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiStraightTie()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::SEVEN, Card::SPADES),
         Card(Card::SIX, Card::HEARTS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::FOUR, Card::SPADES),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::SEVEN, Card::DIAMONDS),
         Card(Card::SIX, Card::CLUBS),
         Card(Card::FIVE, Card::CLUBS),
         Card(Card::FOUR, Card::HEARTS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 == hand2);
}

bool WikiThreeOfAKindWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::EIGHT, Card::DIAMONDS),
         Card(Card::FIVE, Card::SPADES),
         Card(Card::THREE, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::FIVE, Card::CLUBS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::FIVE, Card::DIAMONDS),
         Card(Card::QUEEN, Card::DIAMONDS),
         Card(Card::TEN, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiThreeOfAKindWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::EIGHT, Card::CLUBS),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::EIGHT, Card::DIAMONDS),
         Card(Card::ACE, Card::CLUBS),
         Card(Card::TWO, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::EIGHT, Card::DIAMONDS),
         Card(Card::FIVE, Card::SPADES),
         Card(Card::THREE, Card::CLUBS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiTwoPairWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::KING, Card::HEARTS),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::TWO, Card::CLUBS),
         Card(Card::TWO, Card::DIAMONDS),
         Card(Card::JACK, Card::HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
         Card(Card::TEN, Card::SPADES),
         Card(Card::TEN, Card::CLUBS),
         Card(Card::NINE, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiTwoPairWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::NINE, Card::CLUBS),
         Card(Card::NINE, Card::DIAMONDS),
         Card(Card::SEVEN, Card::DIAMONDS),
         Card(Card::SEVEN, Card::SPADES),
         Card(Card::SIX, Card::HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::NINE, Card::HEARTS),
         Card(Card::NINE, Card::SPADES),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::FIVE, Card::DIAMONDS),
         Card(Card::KING, Card::CLUBS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiTwoPairWin3()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::FOUR, Card::SPADES),
         Card(Card::FOUR, Card::CLUBS),
         Card(Card::THREE, Card::SPADES),
         Card(Card::THREE, Card::HEARTS),
         Card(Card::KING, Card::DIAMONDS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::FOUR, Card::HEARTS),
         Card(Card::FOUR, Card::DIAMONDS),
         Card(Card::THREE, Card::DIAMONDS),
         Card(Card::THREE, Card::CLUBS),
         Card(Card::TEN, Card::SPADES),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiPairWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::TEN, Card::CLUBS),
         Card(Card::TEN, Card::SPADES),
         Card(Card::SIX, Card::SPADES),
         Card(Card::FOUR, Card::HEARTS),
         Card(Card::TWO, Card::HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::NINE, Card::HEARTS),
         Card(Card::NINE, Card::CLUBS),
         Card(Card::ACE, Card::HEARTS),
         Card(Card::QUEEN, Card::DIAMONDS),
         Card(Card::TEN, Card::DIAMONDS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiPairWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::TWO, Card::DIAMONDS),
         Card(Card::TWO, Card::HEARTS),
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::FIVE, Card::CLUBS),
         Card(Card::FOUR, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::TWO, Card::CLUBS),
         Card(Card::TWO, Card::SPADES),
         Card(Card::EIGHT, Card::CLUBS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::THREE, Card::HEARTS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiHighCardWin1()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::ACE, Card::DIAMONDS),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::NINE, Card::SPADES),
         Card(Card::FIVE, Card::CLUBS),
         Card(Card::FOUR, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::KING, Card::CLUBS),
         Card(Card::QUEEN, Card::DIAMONDS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::SEVEN, Card::HEARTS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

bool WikiHighCardWin2()
{
   boost::array<Card,5> cards1 = {
      {
         Card(Card::ACE, Card::CLUBS),
         Card(Card::QUEEN, Card::CLUBS),
         Card(Card::SEVEN, Card::DIAMONDS),
         Card(Card::FIVE, Card::HEARTS),
         Card(Card::TWO, Card::CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(Card::ACE, Card::DIAMONDS),
         Card(Card::TEN, Card::DIAMONDS),
         Card(Card::NINE, Card::SPADES),
         Card(Card::FIVE, Card::CLUBS),
         Card(Card::FOUR, Card::CLUBS),
      }
   };

   PokerHand hand1(cards1);
   PokerHand hand2(cards2);
   return (hand1 > hand2);
}

int main()
{
   if(WikiStraightFlushWin())
   {
      cout << "Straight Flush Win\tOK" << endl;
   }
   else
   {
      cout << "Straight Flush Win\tFAILED" << endl;
   }
   if(WikiStraightFlushTie())
   {
      cout << "Straight Flush Tie\tOK" << endl;
   }
   else
   {
      cout << "Straight Flush Tie\tFAILED" << endl;
   }
   if(WikiFourOfAKindWin1())
   {
      cout << "Four of a Kind Win 1\tOK" << endl;
   }
   else
   {
      cout << "Four of a Kind Win 1\tFAILED" << endl;
   }
   if(WikiFourOfAKindWin2())
   {
      cout << "Four of a Kind Win 2\tOK" << endl;
   }
   else
   {
      cout << "Four of a Kind Win 2\tFAILED" << endl;
   }
   if(WikiFullHouseWin1())
   {
      cout << "Full House Win 1\tOK" << endl;
   }
   else
   {
      cout << "Full House Win 1\tFAILED" << endl;
   }
   if(WikiFullHouseWin2())
   {
      cout << "Full House Win 2\tOK" << endl;
   }
   else
   {
      cout << "Full House Win 2\tFAILED" << endl;
   }
   if(WikiFlushWin1())
   {
      cout << "Flush Win 1\tOK" << endl;
   }
   else
   {
      cout << "Flush Win 1\tFAILED" << endl;
   }
   if(WikiFlushWin2())
   {
      cout << "Flush Win 2\tOK" << endl;
   }
   else
   {
      cout << "Flush Win 2\tFAILED" << endl;
   }
   if(WikiStraightWin())
   {
      cout << "Straight Win\tOK" << endl;
   }
   else
   {
      cout << "Straight Win\tFAILED" << endl;
   }
   if(WikiStraightTie())
   {
      cout << "Straight Tie\tOK" << endl;
   }
   else
   {
      cout << "Straight Tie\tFAILED" << endl;
   }
   if(WikiThreeOfAKindWin1())
   {
      cout << "Three of a Kind Win 1\tOK" << endl;
   }
   else
   {
      cout << "Three of a Kind Win 1\tFAILED" << endl;
   }
   if(WikiThreeOfAKindWin2())
   {
      cout << "Three of a Kind Win 2\tOK" << endl;
   }
   else
   {
      cout << "Three of a Kind Win 2\tFAILED" << endl;
   }
   if(WikiTwoPairWin1())
   {
      cout << "Two Pair Win 1\tOK" << endl;
   }
   else
   {
      cout << "Two Pair Win 1\tFAILED" << endl;
   }
   if(WikiTwoPairWin2())
   {
      cout << "Two Pair Win 2\tOK" << endl;
   }
   else
   {
      cout << "Two Pair Win 2\tFAILED" << endl;
   }
   if(WikiTwoPairWin3())
   {
      cout << "Two Pair Win 3\tOK" << endl;
   }
   else
   {
      cout << "Two Pair Win 3\tFAILED" << endl;
   }
   if(WikiPairWin1())
   {
      cout << "Pair Win 1\tOK" << endl;
   }
   else
   {
      cout << "Pair Win 1\tFAILED" << endl;
   }
   if(WikiPairWin2())
   {
      cout << "Pair Win 2\tOK" << endl;
   }
   else
   {
      cout << "Pair Win 2\tFAILED" << endl;
   }
   if(WikiHighCardWin1())
   {
      cout << "High Card Win 1\tOK" << endl;
   }
   else
   {
      cout << "High Card Win 1\tFAILED" << endl;
   }
   if(WikiHighCardWin2())
   {
      cout << "High Card Win 2\tOK" << endl;
   }
   else
   {
      cout << "High Card Win 2\tFAILED" << endl;
   }
}
