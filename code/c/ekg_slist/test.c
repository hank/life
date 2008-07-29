/* Slist
 * by Erik Gregg
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct _snode_t snode_t;
struct _snode_t {
  snode_t * next;
  uint8_t data;
};

typedef struct {
  snode_t * head;
  snode_t * tail;
  char * name;
} slist_t;

static snode_t * slist_push(slist_t * list, snode_t * node) {
  if(!list->head) { 
    list->head = node;
    return node;
  }

  if(!list->tail) {
    snode_t * node = list->head;
    // No tail.  Find it.
    while(node) {
      list->tail = node;
      node = node->next;
    }
  }

  list->tail->next = node;
  list->tail = node;
}

static uint8_t slist_print(slist_t * list) {
  snode_t * node = list->head;
  uint32_t i = 0;

  if(list->name) printf("Printing %s\n", list->name);
  while(node && i<10) {
    printf("\t%u (%p):\t%u\n", i, node, node->data);
    i++;
    node = node->next;
  }
}

static slist_t * slist_reverse(slist_t * list) {
  snode_t * last = list->head;
  if(!last) return list;
  snode_t * current = last->next;
  if(!current) return list;
  snode_t * next = current->next;

  list->tail = list->head;

  while(current) {
    current->next = last;
    last = current;
    current = next;
    if(current) next = current->next;
  }

  list->head = last;
  list->tail->next = NULL;

  return list;
}

slist_t * slist_init() {
  slist_t * list = calloc(1,sizeof(slist_t));
  return list;
}

int main() {
  uint8_t i;
  slist_t * list;
  snode_t * node;

  list = slist_init();
  list->name = "Test List";

  for(i=1; i<5; i++) {
    node = calloc(1,sizeof(snode_t));
    node->data = i;
    slist_push(list, node);
  }

  slist_print(list);
  slist_reverse(list);
  list->name = "Test List in Reverse";
  slist_print(list);

  return EXIT_SUCCESS;
}
