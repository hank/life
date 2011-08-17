#include <stdio.h>
#include <stdlib.h>
struct list_element {
  struct list_element* next;
  int data;
};

struct list {
  struct list_element* head;
};

int main()
{
  struct list l;
  l.head = calloc(1, sizeof(struct list_element));
  struct list_element* lp = l.head;
  lp->data = 1;
  lp->next = calloc(1, sizeof(struct list_element));
  lp = lp->next;
  lp->data = 2;
  lp->next = calloc(1, sizeof(struct list_element));
  lp = lp->next;
  lp->data = 3;
  lp->next = calloc(1, sizeof(struct list_element));
  lp = lp->next;
  lp->data = 4;

  lp = l.head->next;

  struct list reverse_l;
  reverse_l.head = l.head;
  reverse_l.head->next = NULL;
  struct list_element* tmp;
  while(lp) {
    tmp = reverse_l.head;
    reverse_l.head = lp;
    lp = lp->next;
    reverse_l.head->next = tmp;
  }

  lp = reverse_l.head;
  while(lp) {
    printf("%d\n", lp->data);
    lp = lp->next;
  }

  return 0;
}
