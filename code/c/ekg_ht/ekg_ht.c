#include <stdlib.h>
#include "ekg_ht.h"
#if defined(__x86_64__)
#include "lookup8.c"
typedef uint64_t ekg_hash_t;
#elif defined(__i386__)
#include "lookup3.c"
typedef uint32_t ekg_hash_t;
#else
#error Unsupported Architecture.
#endif

ekg_ht * ht_init(uint32_t n, uint32_t elem_size)
{
  ekg_ht * ht = calloc(1, sizeof(ekg_ht));
  if(!ht) goto init_err;
  ht->data = calloc(n, elem_size);
  return ht;

init_err:
  fprintf(stderr, "Error creating hash table of size %u\n", n);
  return NULL;
}

ekg_ht_elem * ht_find_attach(ekg_ht * ht, char * key, uint32_t len)
{
  ekg_hash_t hash = HASH_FUNC(key, len);
  ekg_ht_elem * maxelem = ht->data + ((ht->m - 1) * sizeof(ekg_ht_elem));
  ekg_ht_elem * elem = ht->data + ((hash % ht->m) * sizeof(ekg_ht_elem));
  uint64_t n = 0;

  while(n < ht->m) {
    if(!elem->set) {
      elem->set = 1;
      return elem;
    }
    if(memcmp(elem->key, key, len) == 0) {
      // Found it.
      return elem;
    }
    else if(elem == maxelem) {
      elem = (ekg_ht_elem *)ht->data;
    }
    else elem += sizeof(ekg_ht_elem);
    n++;
  }
  // Didn't find it, and no empty space in table;
  return NULL;
}

uint8_t ht_delete(ekg_ht_elem * elem) {
  elem->set = 0;
}
