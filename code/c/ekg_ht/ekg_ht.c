#include "ekg_ht.h"

ekg_ht * ht_init(ekg_ht * ht, uint32_t n, uint32_t elem_size)
{
  if(!ht) goto init_err;
  ht->data = calloc(n, elem_size);
  return ht;

init_err:
  fprintf(stderr, "Error creating hash table of size %u\n", n);
  return NULL;
}

ekg_ht_elem * ht_find(ekg_ht * ht, u_char * key, uint32_t len)
{
  u_char * hash = gethash(key, len);
  uint64_t digest = *(uint64_t *)hash + *(uint64_t)(hash + 8);
  ekg_ht_elem * elem = ht->data + (digest % ht->m);
  uint64_t my_n;
  while(elem->key != )

find_err:
  fprintf(stderr, "Could not find element with key %.*s\n", len, key);
  return NULL;
}
snode_t * ht_find_attach(u_char * key, uint32_t len);
uint8_t ht_delete(u_char * key);

#endif
