#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>

inline void fill_subset(int a[], int n, int rank, int fill[])
{
  int i = 0;
  while(rank) {
    if(rank&1) fill[i++] = i;
    rank >>= 1;
    ++i;
  }
}

inline void subset(int a[], int n, int rank)
{
  int i = 0;
  while(rank) {
    if(rank&1) printf("%d ", a[i]);
    rank >>= 1;
    ++i;
  }
}

void random_subset(int a[], int n)
{
  unsigned int rank = rand() % n;
  subset(a, n, rank);
}


void set_cover(int a[], int n)
{
  if(!n) return;
  int num_subsets = pow(2,n) - 1;
  int* current = calloc(1, sizeof(a[0])*n);
  int added = 0;
  int i;
  int 
  while(added < n)
  {
    // Find the subset that contains the most 
    // new items
    fill_subset(a, n, 
  }
}

// Simply create an integer and increment until (2^n)-1
// Only works for sets <= 32/64 elements
void find_all_subsets(int a[], int n)
{
  unsigned int bitfield = 0;
  do {
    //printf("%d\n", bitfield);
    int b = bitfield;
    int i = 0;
    while(b) {
      if(b&1) printf("%d ", a[i]);
      b >>= 1;
      ++i;
    }
    puts("\n");
  } while((float)bitfield++ < pow(2,n) - 1);
}

int main()
{
  srand(time(0));
  int a[] = {3,4,5,6};
  //find_all_subsets(a, sizeof(a)/sizeof(a[0]));
  //random_subset(a, sizeof(a)/sizeof(a[0]));
  set_cover(a, sizeof(a)/sizeof(a[0]));
  return 0;
}
