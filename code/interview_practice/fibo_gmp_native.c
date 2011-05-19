// Uses Native GMP fibo funcs
/*
$ time ./fibo_gmp_native | perl -pe's/(.{80})/$1\n/g' | head -n 2
fib(1073741825) = 78518251460562724635997407205778203278918507605600808196100133
10177653217205848531888621689062426983780448370195196216589344931287157128622259

real  15m36.787s
user  15m25.350s
sys 0m12.110s

This gives a 25% performance boost over fibo_mat.

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

void print_state(mpz_t* f, uint32_t n)
{
  gmp_printf("fib(%d) = %Zd\n", n, f);
}

int main()
{
  mpz_t f;

  mpz_init(f);
  mpz_fib_ui(f, 1073741825);
  print_state(&f, 1073741825);

  return 0;
}
