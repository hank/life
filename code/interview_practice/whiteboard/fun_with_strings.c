#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_copy(const char* str)
{
  char* copy = malloc(strlen(str));
  const char* p = &str[strlen(str)-1];
  int count = 0;
  while(p >= str) {
    copy[count++] = *p;
    --p;
  }
  return copy;
}

void reverse_in_place(char* str)
{
  char* p = str;
  char* q = str + strlen(str) - 1;
  char tmp;
  while(p < q)
  {
    tmp = *p;
    *p = *q;
    *q = tmp;
    ++p; --q;
  }
}

int main()
{
  // String literals have no place here!
  char a[] = "Reverse In Place!";
  reverse_in_place(a);
  printf("In-Place: %s\n", a);
  char* copy = reverse_copy(a);
  printf("Copy: %s\n", copy);
  free(copy);
  return 0;
}
