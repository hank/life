/* Slist
 * by Erik Gregg
 */
#include <stdlib.h>
#include <stdio.h>
#include "ekg_slist.h"

int main() {
  uint32_t i;
  slist_t * list;
  snode_t * node;

  list = slist_init();
  list->name = "Test List";

  for(i=1; i<10; i++) {
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
