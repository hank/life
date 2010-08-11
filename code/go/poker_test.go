package poker_test

import (
   "./card"
   "testing"
)

// Global cards to mess with

func TestFlush(t *testing.T) {
   cards := make(card.Hand, 5)
   for k, _ := range cards {
      cards[k].Suit = 1
      cards[k].Rank = k
   }

   // Check for true case
   if !card.IsFlush(cards) {
      t.Errorf("Failed to detect true Flush")
   }

   // Change one of the suits and retest
   cards[0].Suit = card.DIAMONDS
   if card.IsFlush(cards) {
      t.Errorf("Detected non-flush as flush")
   }
}

func TestStraight(t *testing.T) {
   cards := make(card.Hand, 5)
   for k, _ := range cards {
      cards[k].Suit = k % 4
      cards[k].Rank = k
   }

   // Check for true case
   if !card.IsStraight(cards) {
      t.Errorf("We indeed have a straight")
   }

   cards[0].Rank = card.KING

   // Check for false case
   if card.IsStraight(cards) {
      t.Errorf("Detected non-straight as straight")
   }
}
