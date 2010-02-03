/* Slist
 * by Erik Gregg
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "ekg_ht.h"

struct elem {
  uint32_t mynum;
};
int main()
{
  struct elem e = {1234};
  struct elem * eptr;
  ekg_ht * ht = ht_init(3000, sizeof(struct elem));
  ekg_ht_elem * hte = ht_find_attach(ht, "omg", 3);
  memcpy(hte->data, &e, sizeof(struct elem));
  hte = NULL;
  hte = ht_find_attach(ht, "omg", 3);
  eptr = (struct elem *)hte->data;
  printf("Value: %u\n", eptr->mynum);
  
  return EXIT_SUCCESS;
}
