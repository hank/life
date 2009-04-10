#define GET_CYCLES(x) do { \
  unsigned lo, hi; \
  __asm__ __volatile(".byte 0x0f, 0x31" : "=a"(lo), "=d"(hi)); \
  x = ((unsigned long long)lo)|(((unsigned long long)hi)<<32); \
} while(0)


/* FAST MEMCMP
 * Basically takes advantage of the registers on the processor to do
 * the full word comparisons of the bytes, then switches to stupid
 * memcmp for off-boundary comparisons at the end
 *
 * Testing on x86_64 shows about 8-10 times faster than system memcmp,
 * and 3-4 times faster than forloop memcmp.
 * Will be slower for small comparisons (<250 bytes or so on x86_64)
 */
inline int fmemcmp(const void * buf, const void * buf2, unsigned int buflen) {
  register int diff, i, extra;
  for(i=0; i<buflen; i+=sizeof(unsigned int)) {
    diff = *(unsigned int *)(buf+i) < *(unsigned int *)(buf2 + i);
    if(diff != 0) {
      return diff;
    }
  }
  // Check extra bytes if necessary
  if(i - buflen != 0) {
    extra = sizeof(unsigned int) - (i - buflen);
    for(i=0; i<extra; i++) {
      diff = ((int *)buf)[i] - ((int *)buf2)[i];
      if(diff != 0) {
        return diff;
      }
    }
  }
  return 0;
}
