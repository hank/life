#ifndef __EKG_HT__
#define __EKG_HT__

#if defined(__x86_64__)
#define HASH_FUNC(a,b) hash2(a,b,0x12232122)
#elif defined(__i386__)
#define HASH_FUNC(a,b) hashlittle(a,b,0x12232122)
#else
#error Unsupported Architecture.
#endif

#include <stdint.h>

typedef struct _ekg_ht_elem {
  uint64_t key;
  void * data;
  uint8_t set;
} ekg_ht_elem;

typedef struct _ekg_ht {
  unsigned long n; // Number of insertions
  unsigned long m; // Size of hash table in bytes
  struct _ekg_ht_elem * data; // Hash Table itself
} ekg_ht;

ekg_ht * ht_init(uint32_t n, uint32_t elem_size);
ekg_ht_elem * ht_find_attach(ekg_ht * ht, char * key, uint32_t len);

#endif
