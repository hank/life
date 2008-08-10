/* Slist
 * by Erik Gregg
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "ekg_slist.h"

slist_t * slist_init() {
  slist_t * list = calloc(1,sizeof(slist_t));
  return list;
}

snode_t * slist_push(slist_t * list, snode_t * node) {
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

uint32_t slist_print(slist_t * list) {
  snode_t * node = list->head;
  uint32_t i = 0;

  if(list->name) printf("Printing %s\n", list->name);
  while(node) {
    printf("\t%u (%p):\t%u\tnext = %p\n", i, node, node->data, node->next);
    i++;
    node = node->next;
  }

  return 1;
}

slist_t * slist_reverse(slist_t * list) {
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

