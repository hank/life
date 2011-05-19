#include <stdio.h>
#include <stdint.h>
int main()
{
  int i = 1;
  uint8_t a = 0;
  for(; i <= 100; ++i)
  {
    a = 0;
    if(i % 3 == 0) { a = 1; printf("Fizz"); }
    if(i % 5 == 0) { a = 1; printf("Buzz"); }
    if(!a) printf("%d", i);
    putc('\n', stdout);
  }
  return 0;
}
