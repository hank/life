#import <stdio.h>
#import "Fibo.h"

int main(int argc, const char ** argv)
{
  Fibo *fib = [[Fibo alloc] init];
  int i = 0;
  for(;i<10;i++) [fib next];
  printf("The 10th fibonacci number is: ");
  [fib print];
  printf("\n");

  [fib release];

  return 0;
}
