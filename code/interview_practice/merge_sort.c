#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct _lnode {
    struct _lnode* next;
    struct _lnode* prev;
    int data;
} lnode;

typedef struct {
    struct _lnode* head;
    struct _lnode* tail;
    int size;
} list;

void insert(list* l, int item)
{
    // Initialize if needed
    if(!l->tail) l->tail = l->head = calloc(1,sizeof(lnode));
    else 
    {
        l->tail->next = calloc(1,sizeof(lnode));
        l->tail->next->prev = l->tail;
        l->tail = l->tail->next;
    }
    l->tail->data = item;
    l->size++;
}

void print_list(list* l)
{
    lnode* ln = l->head;
    while(ln)
    {
        printf("%d\n", ln->data);
        ln = ln->next;
    }
}

void list_free(list* l)
{
    lnode* ln = l->head, *t;
    while(ln)
    {
        t = ln->next;
        free(ln);
        ln = t;
    }
}

void swap(list* l, lnode* a, lnode* b)
{
  printf("Swapping %d and %d\n", a->data, b->data);
  lnode* pa, *pb, *ca, *cb;
  pa = a->prev;
  pb = b->prev;
  ca = a->next;
  cb = b->next;
  // Swap a and b's pointers out
  a->prev = pb;
  b->prev = pa;
  a->next = cb;
  b->next = ca;
  // Set the previous and next node ptrs into a and b
  if(pb) pb->next = a;
  if(pa) pa->next = b;
  if(cb) cb->prev = a;
  if(ca) ca->prev = b;
  // Change the list head/tail if necessary
  if(a == l->head) l->head = b;
  else if(b == l->head) l->head = a;
  if(a == l->tail) l->tail = b;
  else if(b == l->tail) l->tail = a;
}

void ms(list* l, lnode* b, lnode* e, int size)
{
    if(!b || !e) return;
    if(size == 2)
    {
        // Normal final case, swap if needed
        if(b->data > e->data) swap(l, b, e);
    }
    else
    {
        // Split, recurse
        int a = size/2;
        lnode* newe = b;
        while(a--) newe = newe->next;
        ms(l, b, newe, size/2);
        ms(l, newe->next, e, size/2);
    }
}

int main()
{
    list* l = calloc(1,sizeof(list));
    insert(l, 4);
    insert(l, 7);
    insert(l, -17);
    insert(l, 45);
    insert(l, 923);
    printf("Unsorted: \n");
    print_list(l);

    // Merge sort the list
    ms(l, l->head, l->tail, l->size);
    printf("Sorted: \n");
    print_list(l);

    list_free(l);
    free(l);
    return 0;
}
