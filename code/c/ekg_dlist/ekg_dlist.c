/* Dlist
 * by Erik Gregg
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "ekg_dlist.h"

dlist_t * dlist_init() {
  dlist_t * list = calloc(1,sizeof(dlist_t));
  return list;
}

dnode_t * dlist_push(dlist_t * list, dnode_t * node) {
  if(!list->head) { 
    list->head = node;
    return node;
  }

  if(!list->tail) {
    dnode_t * node = list->head;
    // No tail.  Find it.
    while(node) {
      list->tail = node;
      node = node->next;
    }
  }

  list->tail->next = node;
  node->prev = list->tail;
  list->tail = node;
}

uint32_t dlist_print(dlist_t * list) {
  dnode_t * node = list->head;
  uint32_t i = 0;

  if(list->name) printf("Printing %s\n", list->name);
  while(node) {
    printf("\t%u (%p):\t%u\n", i, node, node->data);
    i++;
    node = node->next;
  }

  return 1;
}

dlist_t * dlist_reverse(dlist_t * list) {
  dnode_t * current = list->head;
  if(!current) return list;
  dnode_t * tmp;

  list->head = list->tail;
  list->tail = current;

  while(current) {
    tmp = current->next;
    current->next = current->prev;
    current->prev = tmp;
    current = tmp;
  }


  return list;
}

