#include <stdio.h>

int main()
{
  char* order = "dfbcae";
  char input[] = "abcdeeabc";
  char* ocur = order, * cur = input + 1, * pos = input;
  char tmp;
  printf("Input: %s\n", input);
  while(*ocur) {
    while(*cur) {
      if(*cur == *ocur) {
        tmp = *cur;
        *cur = *pos;
        *pos = tmp;
        ++pos;
      }
      ++cur;
    }
    ++ocur;
    cur = pos;
  }
  printf("Output: %s\n", input);
  return 0;
}
