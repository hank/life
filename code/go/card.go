package card

import (
   "fmt"
   "sort"
)

// Ranks
const (
   TWO = iota
   THREE
   FOUR
   FIVE
   SIX
   SEVEN
   EIGHT
   NINE
   TEN
   JACK
   QUEEN
   KING
   ACE
)

// Suits
const (
   HEARTS = iota
   SPADES
   CLUBS
   DIAMONDS
)

// Data structure for a Card in Poker
type Card struct {
   Suit  int
   Rank  int
}

func (c Card) Less(c2 Card) bool {
   return c.Rank < c2.Rank
}

type Hand []Card

// Implement sort.Interface
func (h Hand) Len() int {
   return len(h)
}

func (h Hand) Less(i, j int) bool {
   return h[i].Less(h[j])
}

func (h Hand) Swap(i, j int) {
   h[i], h[j] = h[j], h[i]
}

// Pairs
// Returns the number of pairs and the kinds of pairs
func (h Hand) Pairs() (num_pairs int, ) bool {
   
}

// Check a slice of cards for a Straight
func (hand Hand) IsStraight() bool {
   sort.Sort(hand)
   // Grab the first rank
   var rank int = hand[0].Rank
   num_comparisons := len(hand) - 1
   if hand[len(hand) - 1].Rank == ACE &&
      hand[0].Rank == TWO           {
      // Handle Ace Low straight
      // One less comparison
      num_comparisons--
   }
   for i := 1; i <= num_comparisons; i++ {
      fmt.Println((rank + 1) % 13, hand[i].Rank)
      if((rank + 1) % 13 != hand[i].Rank) {
         fmt.Println((rank + 1) % 13, hand[i].Rank)
         return false
      }
      rank = hand[i].Rank
   }
   return true
}

// Check a slice of cards for a Flush
func (hand Hand) IsFlush() bool {
   // Grab the first suit
   var suit int = hand[0].Suit
   // Compare it to all except itself.
   for _, v := range hand[1:len(hand)] {
      if v.Suit != suit {
         return false
      }
   }
   return true
}

// String representation of a Card
func (c Card) String() (ret string) {
   // Handle Rank
   switch {
      case c.Rank >= TWO && c.Rank <= TEN:
         ret = fmt.Sprintf("%d", c.Rank + 2)
      case c.Rank == JACK:
         ret = "J"
      case c.Rank == QUEEN:
         ret = "Q"
      case c.Rank == KING:
         ret = "K"
      case c.Rank == ACE:
         ret = "A"
   }
   // Handle Suit
   switch c.Suit {
      case SPADES:
         ret += "S"
      case CLUBS:
         ret += "C"
      case DIAMONDS:
         ret += "D"
      case HEARTS:
         ret += "H"
   }
   return
}
