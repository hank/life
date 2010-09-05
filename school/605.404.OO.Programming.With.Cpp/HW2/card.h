// card.h
// Contains the Card class.
#ifndef CARD_H
#define CARD_H
#include <stdint.h>
#include <string>
using std::string;

// Card Class
//   Provides a poker playing card implementation
//
//   Gives an implementation of a playing card that can be initialized to a
//   given Card::SUIT and Card::RANK, or defaulted to the 2 of Spaces (RANK 0,
//   SUIT 0).  The card can then be compared to other cards, converted to
//   different representations, checked for numeric ordering (like in a
//   straight), etc.  All functionality and types of comparisons with other
//   Card objects will be encapsulated in this class.
//
// Copyright (c) 2010, Erik Gregg
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
//     * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above
//     copyright notice, this list of conditions and the following
//     disclaimer in the documentation and/or other materials provided
//     with the distribution.
// 
//     * Neither the name of Erik Gregg nor the names of his
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Erik Gregg
// Date: Tue Jun 15 00:18:02 EDT 2010
class Card
{
   public:
      // The actual numeric values for the cards
      enum RANK
      {
         TWO, THREE, FOUR, FIVE, SIX,
         SEVEN, EIGHT, NINE, TEN,
         JACK, QUEEN, KING, ACE
      };

      // The 4 suits
      enum SUIT
      {
         SPADES = 0,
         HEARTS = 13,
         DIAMONDS = 26,
         CLUBS = 39
      };

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
      bool precedes(const Card& card) const;
      // getSuit
      // Returns the suit of the card.
      SUIT getSuit() const;
      // getCardRank
      // Returns the suit of the card.
      RANK getCardRank() const;
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
inline Card::SUIT Card::getSuit() const
{
   // Suits are assigned to multiples of 13
   // Do some integer truncation magic to get the suit out
   // Since we're truncating, we get the floor of the value / 13
   return static_cast<SUIT>(this->value / 13 * 13);
}

// getCardRank
inline Card::RANK Card::getCardRank() const
{
   // Suits are assigned to multiples of 13
   // Do some integer truncation magic to get the suit out
   // Since we're truncating, we get the floor of the value / 13
   return static_cast<Card::RANK>(this->value % 13);
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
inline bool Card::precedes(const Card& card) const
{
   bool result = false;
   if ( ((getValue() + 1) % 13) == (card.getValue() % 13) )
   {
      // Normal success.  Card value is one more.
      result = true;
   }
   else
   {
      // Otherwise, return false indicating no precession
      result = false;
   }
   return result;
}
#endif // CARD_H
