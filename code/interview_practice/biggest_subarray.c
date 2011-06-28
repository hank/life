#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare_int(const void* a, const void* b)
{
  if(*(int*)a == *(int*)b) {
    return 0;
  }
  return *(int*)a < *(int*)b ? -1 : 1;
}

int main()
{
  int a[] = {1,6,3,5,2,5,2,322,5,3,-2,-5,-7,-2};
  int len = sizeof(a)/sizeof(a[0]);
  qsort(a, len, sizeof(a[0]), compare_int);
  int* cur = a;
  int sum = 0, least_negative = INT_MIN;
  while(cur < &a[len] && *cur < 0) {
    if(*cur > least_negative) least_negative = *cur;
    ++cur;
  }
  while(cur < &a[len]) {
    sum += *cur;
    printf("%d ", *cur++);
  }
  if(!sum) { 
    sum = least_negative;
    printf("%d ", least_negative);
  }
  printf("\nSum: %d\n", sum);
  
  return 0;
}
