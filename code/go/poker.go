package main

import (
   "fmt"
   "./card"
)

func main() {
   cards := make(card.Hand, 5)
   for k, _ := range cards {
      cards[k].Suit = card.DIAMONDS
      cards[k].Rank = k * 2 % 12
   }
   fmt.Println(cards)

   if cards.IsFlush() {
      fmt.Println("We indeed have a flush")
   } else {
      fmt.Println("We don't have a flush")
   }

   // Kill the flush
   cards[0].Suit = card.SPADES
   fmt.Println(cards)
   if cards.IsFlush() {
      fmt.Println("We indeed have a flush")
   } else {
      fmt.Println("We don't have a flush")
   }

   // Make a straight

   for k, _ := range cards {
      cards[k].Suit = k % 4
      cards[k].Rank = k
   }

   fmt.Println(cards)
   if cards.IsStraight() {
      fmt.Println("We indeed have a straight")
   } else {
      fmt.Println("We don't have a straight")
   }

   // Kill the straight
   cards[0].Rank = card.JACK
   fmt.Println(cards)
   if cards.IsStraight() {
      fmt.Println("We indeed have a straight")
   } else {
      fmt.Println("We don't have a straight")
   }

   // Make an ace-low straight
   for k, _ := range cards {
      cards[k].Suit = k % 4
      cards[k].Rank = (k + 12) % 13
   }

   fmt.Println(cards)

   if cards.IsStraight() {
      fmt.Println("We indeed have a straight")
   } else {
      fmt.Println("We don't have a straight")
   }
   
}
