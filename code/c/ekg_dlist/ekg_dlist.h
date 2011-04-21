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

// Initialize a new list
// Returns: Pointer to the newly allocated list
//          User must free
dlist_t * dlist_init();

// Push an element onto the tail of the list
// Returns: The new node
dnode_t * dlist_push(dlist_t * list, dnode_t * node);

// Prints a list, in order
// Returns the number of elements printed
uint32_t dlist_print(dlist_t * list);

// Reverses the list, in place.
// Returns a pointer to the reversed list
dlist_t * dlist_reverse(dlist_t * list);

#endif
