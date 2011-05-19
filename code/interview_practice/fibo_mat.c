// Quick proof of concept to calculate large fibonacci numbers with matrix
// multiplication.  Assuming constant-time arithmetic (which isn't the case
// since we're using GMP, but whatever), this yields the k-th fibo number
// in O(log(k)) time, which is pretty awesome.  This thing pumps out
// the 1,000,000th+ fibo number in less than a second.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

void print_state(mpz_t* fm2, mpz_t* fm1, mpz_t* f, uint32_t n)
{
  //gmp_printf("Result:\t%Zd\n\t%Zd\n\t%Zd\n", 
  //            fm2, fm1, f);
  gmp_printf("fib(%d) = %Zd\n", n, f);
}
#define NEXT_FIB() \
  mpz_set(oldfm1, fm1); \
  mpz_set(oldf, f); \
  mpz_mul(f, f, f); \
  mpz_mul(tmp, fm1, fm1); \
  mpz_add(f, f, tmp); \
  mpz_mul(fm1, oldf, fm1); \
  mpz_mul(tmp, oldfm1, fm2); \
  mpz_add(fm1, fm1, tmp); \
  mpz_set(tmp, fm2); \
  mpz_mul(fm2, oldfm1, oldfm1); \
  mpz_mul(tmp, tmp, tmp); \
  mpz_add(fm2, fm2, tmp); \
  n += i; \
  i *= 2;

int main()
{
  mpz_t fm2, fm1, f;
  uint32_t n = 2;
  uint32_t i = 1;

  mpz_inits(fm2, fm1, f, NULL);
  // Initial conditions: 0 1 1
  mpz_set_si(fm2, 0);
  mpz_set_si(fm1, 1);
  mpz_set_si(f, 1);
  printf("Initial state:\n");
  print_state(&fm2, &fm1, &f, n);

  // Let the games begin!
  // |3 2|   |3 2| 
  // |2 1|   |2 1|
  // f = 3 * 3 + 2 * 2 = 9 + 4 = 13
  //     f * f + fm1 * fm1
  // fm1 = 3 * 2 + 2 * 1 = 8
  //       f * fm1 + fm1 * fm2
  // fm2 = 2 * 2 + 1 * 1 = 5
  //       fm1 * fm1 + fm2 * fm2
  mpz_t oldf, oldfm1, tmp;
  mpz_inits(oldf, oldfm1, tmp, NULL);

  NEXT_FIB();

  printf("After first round:\n");
  print_state(&fm2, &fm1, &f, n);

  NEXT_FIB();

  printf("After second round:\n");
  print_state(&fm2, &fm1, &f, n);

  NEXT_FIB();

  printf("After third round:\n");
  print_state(&fm2, &fm1, &f, n);

  // Now, it's time to get funky.
  int g = 0;
  for(;g<20;++g)
  {
    NEXT_FIB();
  }
  print_state(&fm2, &fm1, &f, n);

  return 0;
}
