#include <stdio.h>
#include <string.h>
#define HEAP_SIZE 128

struct heap {
  int n;
  int arr[HEAP_SIZE + 1];
};

void swap(int* a, int* b) {
  int tmp = *a; *a = *b; *b = tmp;
}

int get_parent(int idx) {
  if(idx > 1) return idx/2;
  else return -1;
}

void bubble_up(struct heap* h, int idx) {
  int parent = get_parent(idx);
  if(parent < 0) return;
  if(h->arr[parent] > h->arr[idx]) {
    swap(&h->arr[parent], &h->arr[idx]);
    bubble_up(h, parent);
  }
}

void bubble_down(struct heap* h, int idx) {
  int left_child = idx * 2;
  int right_child = idx * 2 + 1;
  int max = idx;
  if(left_child <= h->n && h->arr[left_child] < h->arr[max]) 
    max = left_child;
  if(right_child <= h->n && h->arr[right_child] < h->arr[max])
    max = right_child;
  if(max != idx) {
    swap(&h->arr[max], &h->arr[idx]);
    bubble_down(h, max);
  }
}

int insert(struct heap* h, int t) {
  if(h->n >= HEAP_SIZE + 1)
         return -1;
  h->arr[h->n + 1] = t;
  bubble_up(h, h->n + 1);
  return h->n++;
}

int pop(struct heap* h) {
  int head = h->arr[1];
  h->arr[1] = h->arr[h->n];
  --h->n;
  bubble_down(h, 1);
  return head;
}

void print_heap(struct heap* h) {
  int i = 1;
  while(i <= h->n) {
    printf("%d ", h->arr[i]);
    ++i;
  }
}

void heapify(struct heap* h)
{
  // Build a heap from an unsorted h->arr
  // n must be set properly.
  // Bottom-up implementation
  int idx = h->n/2;
  while(idx > 1)
  {
    bubble_down(h, idx);
    --idx;
  }
}

int main()
{
  int i;
  struct heap foo = {.n = 0};
  insert(&foo, 5);
  insert(&foo, 10);
  insert(&foo, 4);
  insert(&foo, 5);
  insert(&foo, 8);
  for(i=0;i<5;++i) {
    print_heap(&foo);
    printf("%d\n", pop(&foo));
  }

  // Try out heapify;
  struct heap bheap = {.n = 20};
  int nums[] = {4,2,3,5,6,2,21,3,45,4,34,2,3,4,456,3,2,3,5,3};
  memcpy(bheap.arr + 1, nums, sizeof(int)*20);
  heapify(&bheap);
  print_heap(&bheap);
  for(i=0;i<20;++i) {
    printf("%d\n", pop(&bheap));
  }
  return 0;
}
