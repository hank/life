package main

import (
   "fmt"
)

// Generates a channel of numbers
func generate() chan int {
   ch := make(chan int)
   go func() {
      for i := 2; ; i++ {
         ch <- i
      }
   }()
   return ch
}

// Generates a filtered channel of numbers
func filter(in chan int, prime int) chan int {
   out := make(chan int)
   go func() {
      for {
         if i := <-in; i % prime != 0 {
            out <- i
         }
      }
   }()
   return out
}

// Generates a channel of sieved primes
func sieve() chan int {
   out := make(chan int)
   go func() {
      ch := generate()
      for {
         prime := <-ch
         out <- prime
         ch = filter(ch, prime)
      }
   }()
   return out
}

func main() {
   primes := sieve()
   for {
      fmt.Println(<- primes)
   }
}
