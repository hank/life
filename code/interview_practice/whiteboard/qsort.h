#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int* i, int* j)
{ int tmp = *i; *i = *j; *j = tmp; }

// Takes list, left/right pointers, and pivot index
// Returns new pivot index
int partition(int* a, int n, int pivotidx)
{
  int* left = a, * right = &a[n-1];
  int* save = a;
  int pivot = a[pivotidx];
  swap(&a[pivotidx], right);
  while(left < right) {
    if(*left < pivot) {
      swap(left, save++);
    }
    ++left;
  }
  swap(save, right);
  return save - a;
}

void quicksort(int* a, int n)
{
  if(n < 2) return;
  int pividx = rand() % n;
  int new_pividx = partition(a, n, pividx);
  quicksort(a, new_pividx);
  quicksort(&a[new_pividx+1], n - new_pividx - 1);
}

int quickselect(int* a, int n, int rank)
{
  if(n < 2) return a[0];
  int pividx = rand() % n;
  int new_pividx = partition(a, n, pividx);
  int pivrank = new_pividx + 1;
  if(rank == pivrank) {
    return a[new_pividx];
  }
  else if(rank < pivrank) {
    return quickselect(a, new_pividx, rank);
  }
  else {
    return quickselect(&a[new_pividx] + 1, 
                       n - new_pividx - 1, 
                       rank - pivrank);
  }
}
