#include <stdlib.h>
#include <stdio.h>
#include "ekg_dlist.h"

int main() {
  uint32_t i;
  dlist_t * list;
  dnode_t * node;

  list = dlist_init();
  list->name = "Test List";

  for(i=1; i<10; i++) {
    node = calloc(1,sizeof(dnode_t));
    node->data = i;
    dlist_push(list, node);
  }

  dlist_print(list);
  dlist_reverse(list);
  list->name = "Test List in Reverse";
  dlist_print(list);

  return EXIT_SUCCESS;
}
