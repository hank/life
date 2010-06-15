#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <boost/array.hpp>
#include "pokerhand.h"
// Use the Poker namespace.
using namespace EGPoker;

TEST(Card, CardIntEqualsOperator)
{
   Card c(SEVEN, SPADES);
   ASSERT_EQ((int)c, SEVEN + SPADES);
}

TEST(Card, CardEqualsOperator)
{
   Card c(QUEEN, SPADES);
   Card d(QUEEN, HEARTS);
   ASSERT_EQ(c, d);
}

TEST(Card, CardValueComparisons)
{
   // AD > 7S
   Card c(SEVEN, SPADES);
   Card d(ACE, DIAMONDS);
   ASSERT_GT(d, c);
   ASSERT_LT(c, d);
   ASSERT_NE(c, d);

   // KS > QH
   c = QUEEN + HEARTS;
   d = KING + SPADES;
   ASSERT_GT(d, c);
   ASSERT_LT(c, d);
   ASSERT_NE(c, d);

   // KS == KC
   c = KING + CLUBS;
   d = KING + SPADES;
   ASSERT_EQ(c, d);
}

TEST(PokerHand, CreateHand)
{
   // Initialize Seven High Straight
   Card card1 = Card(SEVEN + HEARTS);
   Card card2 = Card(SIX, HEARTS);
   Card card3 = Card(FIVE + SPADES);
   Card card4 = Card(FOUR + HEARTS);
   Card card5 = Card(THREE + HEARTS);
   PokerHand p(card1, card2, card3, card4, card5);
}

TEST(PokerHand, CreateHandBoostArray)
{
   boost::array<Card,5> cards = {
      {
         Card(TWO, SPADES),
         Card(KING, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(ACE, SPADES),
         Card(THREE, CLUBS),
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
         Card(THREE, SPADES),
         Card(KING, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(ACE, SPADES),
         Card(FOUR, CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have a pair.
   ASSERT_EQ(t.getHandRank(), HIGH_CARD);
   // Make sure high card is an Ace
   ASSERT_EQ((int)t.getHighCard().getCardRank(), ACE);
}

TEST(PokerHand, CalculatePair)
{
   boost::array<Card,5> cards = {
      {
         Card(THREE, SPADES),
         Card(KING, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(ACE, SPADES),
         Card(THREE, CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have a pair.
   ASSERT_EQ(t.getHandRank(), PAIR);
   // Make sure high card is an Ace
   ASSERT_EQ((int)t.getHighCard().getCardRank(), ACE);
}

TEST(PokerHand, CalculateTwoPair)
{
   boost::array<Card,5> cards = {
      {
         Card(THREE, SPADES),
         Card(KING, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(QUEEN, SPADES),
         Card(THREE, CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), TWO_PAIR);
   // Make sure high card is a King
   ASSERT_EQ((int)t.getHighCard().getCardRank(), KING);
}

TEST(PokerHand, CalculateThreeOfAKind)
{
   boost::array<Card,5> cards = {
      {
         Card(EIGHT, SPADES),
         Card(QUEEN, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(QUEEN, SPADES),
         Card(TWO, CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), THREE_OF_A_KIND);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), QUEEN);
}

TEST(PokerHand, CalculateStraight)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(EIGHT, DIAMONDS),
         Card(QUEEN, HEARTS),
         Card(JACK, SPADES),
         Card(TEN, CLUBS),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), STRAIGHT);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), QUEEN);
}

TEST(PokerHand, CalculateFlush)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(TWO, SPADES),
         Card(QUEEN, SPADES),
         Card(JACK, SPADES),
         Card(TEN, SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), FLUSH);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), QUEEN);
}

TEST(PokerHand, CalculateFullHouse)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(NINE, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), FULL_HOUSE);
   // Make sure high card is a Jack
   ASSERT_EQ((int)t.getHighCard().getCardRank(), JACK);
}

TEST(PokerHand, CalculateFourOfAKind)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(JACK, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), FOUR_OF_A_KIND);
   // Make sure high card is a King
   ASSERT_EQ((int)t.getHighCard().getCardRank(), JACK);
}

TEST(PokerHand, CalculateStraightFlush)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(EIGHT, SPADES),
         Card(QUEEN, SPADES),
         Card(JACK, SPADES),
         Card(TEN, SPADES),
      }
   };
   PokerHand t(cards);
   // Make sure we have 2 pair.
   ASSERT_EQ(t.getHandRank(), STRAIGHT_FLUSH);
   // Make sure high card is a Queen
   ASSERT_EQ((int)t.getHighCard().getCardRank(), QUEEN);
}

TEST(PokerHand, AssignmentA)
{
   boost::array<Card,5> cards1 = {
      {
         Card(SEVEN, HEARTS),
         Card(SIX, HEARTS),
         Card(FIVE, HEARTS),
         Card(FOUR, HEARTS),
         Card(THREE, HEARTS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(FIVE, SPADES),
         Card(FOUR, SPADES),
         Card(THREE, SPADES),
         Card(TWO, SPADES),
         Card(ACE, SPADES),
      }
   };

   PokerHand hand1(cards1);
   ASSERT_EQ(hand1.getHandRank(), STRAIGHT_FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), STRAIGHT_FLUSH);
   ASSERT_EQ((int)hand2.getHighCard(), ACE);
   // Hand 1 beats Hand 2
   ASSERT_TRUE(hand1 > hand2);
}

TEST(PokerHand, AssignmentB)
{
   boost::array<Card,5> cards1 = {
      {
         Card(JACK, CLUBS),
         Card(TEN, CLUBS),
         Card(NINE, CLUBS),
         Card(EIGHT, CLUBS),
         Card(SEVEN, CLUBS),
      }
   };

   boost::array<Card,5> cards2 = {
      {
         Card(JACK, DIAMONDS),
         Card(TEN, DIAMONDS),
         Card(NINE, DIAMONDS),
         Card(EIGHT, DIAMONDS),
         Card(SEVEN, DIAMONDS),
      }
   };

   PokerHand hand1(cards1);
   ASSERT_EQ(hand1.getHandRank(), STRAIGHT_FLUSH);
   PokerHand hand2(cards2);
   ASSERT_EQ(hand2.getHandRank(), STRAIGHT_FLUSH);
   // A tie.
   ASSERT_TRUE(hand1 == hand2);
}

TEST(PokerHand, FullHouseFirstRankMatch)
{
   boost::array<Card,5> cards = {
      {
         Card(NINE, SPADES),
         Card(NINE, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(EIGHT, SPADES),
         Card(EIGHT, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}

TEST(PokerHand, FullHouseFirstRankMatchReverse)
{
   boost::array<Card,5> cards = {
      {
         Card(QUEEN, SPADES),
         Card(QUEEN, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(EIGHT, SPADES),
         Card(EIGHT, HEARTS),
         Card(JACK, CLUBS),
         Card(JACK, DIAMONDS),
         Card(JACK, SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}

TEST(PokerHand, AceHighStraightVsAceLowStraight)
{
   boost::array<Card,5> cards = {
      {
         Card(ACE, SPADES),
         Card(KING, HEARTS),
         Card(QUEEN, CLUBS),
         Card(JACK, DIAMONDS),
         Card(TEN, SPADES),
      }
   };
   PokerHand t(cards);
   boost::array<Card,5> cards2 = {
      {
         Card(ACE, SPADES),
         Card(TWO, HEARTS),
         Card(THREE, CLUBS),
         Card(FOUR, DIAMONDS),
         Card(FIVE, SPADES),
      }
   };
   PokerHand u(cards2);
   ASSERT_TRUE(t > u);
}
