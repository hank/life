#include <string>
using std::string;
#include "card.h"
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
      break;
  }
  return s;
}
