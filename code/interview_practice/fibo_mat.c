/*
 Quick proof of concept to calculate large fibonacci numbers with matrix
 multiplication.  Assuming constant-time arithmetic (which isn't the case since
 we're using GMP), this yields the k-th fibo number in O(log(k)) time, which is
 pretty awesome.  This thing pumps out the 1,000,000th+ fibo number in less than a second.

 Run it like so: ./fibo_mat 8000000
 Will get you back a fibo over what you asked for.
 Still working on memo-izing to allow for more accuracy.

./fibo_mat 1000000 | perl -pe's/(.{80})/$1\n/g' | head -n 2
fib(1048577) =
19202837189514814299644801922187574587123601490134274290586059452...

 It takes almost 2 minutes to calculate the 134217729th fibo on a 4W Intel
 Atom:

$ time ./fibo_mat 100000000 | perl -pe's/(.{80})/$1\n/g' | head -n 2
fib(134217729) = 12999783985026352071541803650219874172233205507273747186215675
6903157624119158920577761460705593601274785365466973463913109293946532504862452
09...

real  1m49.361s
user  1m48.090s
sys 0m1.380s

 Verified here using Approximation: http://bit.ly/lZjqz6

fib(134217729)=12999783... [28049847 digits] approx
*/

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

// Yeah, I hate macros, but I got lazy
// So, sue me.
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

int main(int argc, char** argv)
{
  mpz_t fm2, fm1, f;
  uint32_t n = 2;
  uint32_t i = 1;

  mpz_inits(fm2, fm1, f, NULL);
  // Initial conditions: 0 1 1
  mpz_set_si(fm2, 0);
  mpz_set_si(fm1, 1);
  mpz_set_si(f, 1);

/*
  printf("Initial state:\n");
  print_state(&fm2, &fm1, &f, n);
*/
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

/*
  NEXT_FIB();

  printf("After first round:\n");
  print_state(&fm2, &fm1, &f, n);

  NEXT_FIB();

  printf("After second round:\n");
  print_state(&fm2, &fm1, &f, n);

  NEXT_FIB();

  printf("After third round:\n");
  print_state(&fm2, &fm1, &f, n);
*/
  // Time to do what we were asked.
  if(argc < 2) 
  {
    printf("Give me a number, brah!\n");
    return 1;
  }
  uint32_t g = strtol(argv[1], NULL, 10);
  while(n<g)
  {
    NEXT_FIB();
  }
  print_state(&fm2, &fm1, &f, n);

  return 0;
}
