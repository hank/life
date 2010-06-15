#ifndef POKER_HAND
#define POKER_HAND

#include <string>
using std::string;
#include <algorithm> // for std::sort
#include <stdint.h>
#include "card.h"

// Boost
#include <boost/array.hpp>

// Add to the EGPoker namespace
namespace EGPoker
{
   // Hand ranks, in order of awesomeness.
   enum HandRank
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
   // PokerHand Class
   //   Provides a structure for storing 5 cards and various routines to evaluate
   //   Poker gameplay.
   //
   //   The PokerHand contains 5 Card objects which must be given either as a
   //   Boost.Array or as 5 parameters upon initialization.  The Cards are then
   //   stored in an array and sorted in ascending order.  The hand is then
   //   evaluated for all the possible Poker HandRanks.  Comparison operations
   //   are offered for comparing to other PokerHand objects.  Basic printing
   //   functions are also available.
   //
   //   Copyright (c) 2010, Erik Gregg
   //   All rights reserved.
   //   Redistribution and use in source and binary forms, with or without
   //   modification, are permitted provided that the following conditions are
   //   met:
   //   
   //       * Redistributions of source code must retain the above copyright
   //       notice, this list of conditions and the following disclaimer.
   //
   //       * Redistributions in binary form must reproduce the above copyright 
   //       notice, this list of conditions and the following disclaimer in the
   //       documentation and/or other materials provided with the distribution.
   //
   //       * Neither the name of Erik Gregg nor the names of its contributors
   //       may be used to endorse or promote products derived from this software
   //       without specific prior written permission.
   //   
   //   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   //   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
   //   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   //   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   //   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   //   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   //   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   //   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   //   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   //   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   //   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   //
   //   Author: Erik Gregg
   //   Date: Tue Jun 15 00:18:02 EDT 2010
   class PokerHand
   {
      public:
         // Boost.Array constructor
         // The Boost.Array template parameters guarantee the size.
         // Misuse will result in a compile error.
         PokerHand(boost::array<Card, 5>& array);

         // 5 Card param constructor
         PokerHand(Card& card1, Card& card2, Card& card3, 
               Card& card4, Card& card5);

         // Comparison operations
         // Greater Than
         bool operator > (const PokerHand& otherHand) const;
         // Greater Than or Equal
         bool operator >= (const PokerHand& otherHand) const;
         // Less Than
         bool operator < (const PokerHand& otherHand) const;
         // Less Than or Equal
         bool operator <= (const PokerHand& otherHand) const;
         // Equal
         bool operator == (const PokerHand& otherHand) const;
         // Not Equal
         bool operator != (const PokerHand& otherHand) const;

         // getHandRank returns the current rank of the hand These may be
         // compared such that the higher the HandRank, the stronger the hand.
         // Defaults to HIGH_CARD, since that is always the base case.
         const HandRank getHandRank() const;
         // getHighCard returns the current overall high card.  This is the highest
         // card in the hand regardless of HandRank.
         const Card& getHighCard() const;
         // Simply return the requested card
         const Card& getCard(uint8_t index) const;
         // Simply return a writable version of the card
         Card& getCard(uint8_t index);
         // String cast operator
         operator string() const;

      private:
         // getFirstRank returns the high card for the first rank.  For
         // PokerHands with multiple ranks, such as TWO_PAIR or FULL_HOUSE,
         // this is the stronger of the two parts.  That is to say, the
         // higher pair or the three-of-a-kind respectively for the
         // afore-mentioned HandRanks.
         const CardRank getFirstRank() const;
         // getSecondRank returns the high card for the second rank.  This is
         // only used by PokerHands that have more than one rank, and has
         // undefined behavior if used outside those bounds.
         const CardRank getSecondRank() const;
         // Set the rank of the hand to a specific value.  May only be used
         // internally.
         void setHandRank(const HandRank& rank);
         // Set the first rank.  Takes a Card object argument, and extracts
         // the CardRank.
         void setFirstRank(const Card& card);
         // Set the second rank.  Takes a Card object argument, and extracts
         // the CardRank.
         void setSecondRank(const Card& card);
         // Calculates the hand rank based on the cards in hand.  This calls
         // all the routines for ranking decisions.
         void calculateRank();
         // checkFlush checks if all cards have the same suit.
         void checkFlush();
         // checkStraight iteratively deduces if a straight exists in the
         // PokerHand
         void checkStraight();
         // checkPairs finds any numerically matching subsets of the
         // PokerHand
         void checkPairs();
         // compare compares this object to another PokerHand and deduces
         // superiority.
         int8_t compare(const PokerHand& otherHand) const;

         static const uint8_t numCards = 5; // We've got 5 cards
         HandRank handRank; // Holds the rank of the hand
         CardRank firstRank; // Holds the first rank
         CardRank secondRank; // Holds the second rank
         Card cards[numCards]; // Holds cards for the hand
   };

   // setHandRank
   inline void PokerHand::setHandRank(const HandRank& handRank) 
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
   inline const HandRank PokerHand::getHandRank() const
   {
      return this->handRank;
   }

   // getFirstRank
   inline const CardRank PokerHand::getFirstRank() const
   {
      return this->firstRank;
   }

   // getSecondRank
   inline const CardRank PokerHand::getSecondRank() const
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
} // EGPoker namespace
#endif // POKER_HAND
