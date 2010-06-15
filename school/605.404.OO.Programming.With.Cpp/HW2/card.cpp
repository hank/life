#include <string>
using std::string;
#include "card.h"
namespace EGPoker
{
   // String cast operator
   // Produces something that looks like this:
   //    2H 3D 4S 5C JD
   // Suits are C = Clubs, D = Diamonds, H = Hearts, S = Spades
   Card::operator string() const
   {
      std::string s;
      // Execute switch for the card
      switch(static_cast<uint8_t>(*this) % 13)
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
      switch(getSuit())
      {
         case SPADES:
            s += "S";
            break;
         case HEARTS:
            s += "H";
            break;
         case DIAMONDS:
            s += "D";
            break;
         case CLUBS:
            s += "C";
            break;
         default:
            s += "?";
            break;
      }
      return s;
   }
} // EGPoker namespace
