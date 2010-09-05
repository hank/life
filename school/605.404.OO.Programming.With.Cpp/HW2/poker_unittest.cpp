#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <boost/array.hpp>
#include "pokerhand.h"
// Use the Poker namespace.

TEST(Card, CardIntEqualsOperator)
{
   Card c(Card::SEVEN, Card::SPADES);
   ASSERT_EQ((int)c, Card::SEVEN + Card::SPADES);
}

TEST(Card, CardEqualsOperator)
{
   Card c(Card::QUEEN, Card::SPADES);
   Card d(Card::QUEEN, Card::HEARTS);
   ASSERT_EQ(c, d);
}

TEST(Card, CardValueComparisons)
{
   // AD > 7S
   Card c(Card::SEVEN, Card::SPADES);
   Card d(Card::ACE, Card::DIAMONDS);
   ASSERT_GT(d, c);
   ASSERT_LT(c, d);
   ASSERT_NE(c, d);

   // KS > QH
   c = Card::QUEEN + Card::HEARTS;
   d = Card::KING + Card::SPADES;
   ASSERT_GT(d, c);
   ASSERT_LT(c, d);
   ASSERT_NE(c, d);

   // KS == KC
   c = Card::KING + Card::CLUBS;
   d = Card::KING + Card::SPADES;
   ASSERT_EQ(c, d);
}

TEST(PokerHand, CreateHand)
{
   // Initialize Seven High Straight
   Card card1 = Card(Card::SEVEN + Card::HEARTS);
   Card card2 = Card(Card::SIX, Card::HEARTS);
   Card card3 = Card(Card::FIVE + Card::SPADES);
   Card card4 = Card(Card::FOUR + Card::HEARTS);
   Card card5 = Card(Card::THREE + Card::HEARTS);
   PokerHand p(card1, card2, card3, card4, card5);
}

TEST(PokerHand, CreateHandBoostArray)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::TWO, Card::SPADES),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::ACE, Card::SPADES),
         Card(Card::THREE, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Expect it to be sorted by card value
   ASSERT_EQ((string)t, "2S 3C QH KD AS");
}

TEST(PokerHand, CalculateHighCard)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::THREE, Card::SPADES),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::ACE, Card::SPADES),
         Card(Card::FOUR, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have a pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::HIGH_CARD);
   // Make sure high card is an Ace
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::ACE);
}

TEST(PokerHand, CalculatePair)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::THREE, Card::SPADES),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::ACE, Card::SPADES),
         Card(Card::THREE, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have a pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::PAIR);
   // Make sure high card is an Ace
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::ACE);
}

TEST(PokerHand, CalculateTwoPair)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::THREE, Card::SPADES),
         Card(Card::KING, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::THREE, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::TWO_PAIR);
   // Make sure high card is a King
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::KING);
}

TEST(PokerHand, CalculateThreeOfAKind)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::QUEEN, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::TWO, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::THREE_OF_A_KIND);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::QUEEN);
}

TEST(PokerHand, CalculateStraight)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::EIGHT, Card::DIAMONDS),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::JACK, Card::SPADES),
         Card(Card::TEN, Card::CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::STRAIGHT);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::QUEEN);
}

TEST(PokerHand, CalculateFlush)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::TWO, Card::SPADES),
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::JACK, Card::SPADES),
         Card(Card::TEN, Card::SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::FLUSH);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::QUEEN);
}

TEST(PokerHand, CalculateFullHouse)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::NINE, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::FULL_HOUSE);
   // Make sure high card is a Jack
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::JACK);
}

TEST(PokerHand, CalculateFourOfAKind)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::JACK, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::FOUR_OF_A_KIND);
   // Make sure high card is a King
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::JACK);
}

TEST(PokerHand, CalculateStraightFlush)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::JACK, Card::SPADES),
         Card(Card::TEN, Card::SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), PokerHand::STRAIGHT_FLUSH);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), Card::QUEEN);
}

TEST(PokerHand, AceHighStraightVsAceLowStraight)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::ACE, Card::SPADES),
         Card(Card::KING, Card::HEARTS),
         Card(Card::QUEEN, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::TEN, Card::SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(Card::ACE, Card::SPADES),
         Card(Card::TWO, Card::HEARTS),
         Card(Card::THREE, Card::CLUBS),
         Card(Card::FOUR, Card::DIAMONDS),
         Card(Card::FIVE, Card::SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}

TEST(PokerHand, FullHouseFirstRankMatch)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::NINE, Card::SPADES),
         Card(Card::NINE, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}

TEST(PokerHand, FullHouseFirstRankMatchReverse)
{
   boost::array<Card,5> cards = {
      {
         Card(Card::QUEEN, Card::SPADES),
         Card(Card::QUEEN, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(Card::EIGHT, Card::SPADES),
         Card(Card::EIGHT, Card::HEARTS),
         Card(Card::JACK, Card::CLUBS),
         Card(Card::JACK, Card::DIAMONDS),
         Card(Card::JACK, Card::SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}


TEST(PokerHand, WikiStraightFlushWin)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::STRAIGHT_FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::STRAIGHT_FLUSH);
   ASSERT_EQ((int)hand2.getHighCard(), Card::ACE);
   // Hand 1 beats Hand 2
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiStraightFlushTie)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::STRAIGHT_FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::STRAIGHT_FLUSH);
   ASSERT_TRUE(hand1 == hand2);
}

TEST(PokerHand, WikiFourOfAKindWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FOUR_OF_A_KIND);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FOUR_OF_A_KIND);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiFourOfAKindWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FOUR_OF_A_KIND);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FOUR_OF_A_KIND);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiFullHouseWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FULL_HOUSE);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FULL_HOUSE);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiFullHouseWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FULL_HOUSE);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FULL_HOUSE);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiFlushWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FLUSH);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiFlushWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::FLUSH);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiStraightWin)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::STRAIGHT);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::STRAIGHT);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiStraightTie)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::STRAIGHT);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::STRAIGHT);
   ASSERT_TRUE(hand1 == hand2);
}

TEST(PokerHand, WikiThreeOfAKindWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::THREE_OF_A_KIND);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::THREE_OF_A_KIND);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiThreeOfAKindWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::THREE_OF_A_KIND);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::THREE_OF_A_KIND);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiTwoPairWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::TWO_PAIR);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::TWO_PAIR);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiTwoPairWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::TWO_PAIR);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::TWO_PAIR);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiTwoPairWin3)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::TWO_PAIR);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::TWO_PAIR);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiPairWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::PAIR);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::PAIR);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiPairWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::PAIR);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::PAIR);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiHighCardWin1)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::HIGH_CARD);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::HIGH_CARD);
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, WikiHighCardWin2)
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
   ASSERT_EQ(hand1.getHandRank(), PokerHand::HIGH_CARD);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), PokerHand::HIGH_CARD);
   ASSERT_TRUE(hand1 > hand2);
}
