#include <stdio.h>
#define HEAP_SIZE 128

struct heap {
  int n;
  int arr[HEAP_SIZE];
};

void swap(int* a, int* b) {
  int tmp = *a; *a = *b; *b = tmp;
}

int get_parent(int idx) {
  if(idx > 0) return idx/2;
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
  if(left_child < h->n && h->arr[left_child] < h->arr[max]) 
    max = left_child;
  if(right_child < h->n && h->arr[right_child] < h->arr[max])
    max = right_child;
  if(max != idx) {
    swap(&h->arr[max], &h->arr[idx]);
    bubble_down(h, max);
  }
}

int insert(struct heap* h, int t) {
  if(h->n >= HEAP_SIZE)
         return -1;
  h->arr[h->n] = t;
  bubble_up(h, h->n);
  return h->n++;
}

int pop(struct heap* h) {
  int head = h->arr[0];
  h->arr[0] = h->arr[h->n - 1];
  --h->n;
  bubble_down(h, 0);
  return head;
}

void print_heap(struct heap* h) {
  int i = 0;
  while(i < h->n) {
    printf("%d ", h->arr[i]);
    ++i;
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
  return 0;
}
