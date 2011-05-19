#include <stdio.h>
#include <stdlib.h>
#include "factorial.h"

int main()
{
  Factorial f(10);
  printf("F is %i\n", (int)f);
  return EXIT_SUCCESS;
}
