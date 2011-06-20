#include <stdio.h>

void swap(int* t, int* v)
{
  int tmp = *t;
  *t = *v;
  *v = tmp;
}

void insertion_sort(int* list, int size)
{
  int* cur = list;
  int* min, *cur2;
  if(size < 2) return;
  while(cur < &list[size-1]) // 1 from end
  {
    min = cur2 = cur + 1;
    while(cur2 <= &list[size-1]) // At end
    {
      if(*min > *cur2) min = cur2;
      ++cur2;
    }
    if(*min < *cur) swap(min, cur);
    ++cur;
  }
}

int main()
{
  int foo[] = {3, 4, 2, 6, 4, 7, 3, 1};
  int size = 8;
  insertion_sort(foo, size);
  int i = 0;
  for(; i < size; ++i)
  {
    printf("%d\n", foo[i]);
  }
  return 0;
}
