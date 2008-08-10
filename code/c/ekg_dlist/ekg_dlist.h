/* Dlist
 * by Erik Gregg
 */
#ifndef __EKG_DLIST__
#define __EKG_DLIST__

#include <stdio.h>
#include <stdint.h>

typedef struct _dnode_t dnode_t;
struct _dnode_t {
  dnode_t * next;
  dnode_t * prev;
  uint32_t data;
};

typedef struct {
  dnode_t * head;
  dnode_t * tail;
  char * name;
} dlist_t;

dlist_t * dlist_init();
dnode_t * dlist_push(dlist_t * list, dnode_t * node);
uint32_t dlist_print(dlist_t * list);
dlist_t * dlist_reverse(dlist_t * list);

#endif
