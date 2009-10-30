/* ekg_sys.h
 * Various niceties for programming.
 */

#define GET_CYCLES(x) do { \
  unsigned lo, hi; \
  __asm__ __volatile(".byte 0x0f, 0x31" : "=a"(lo), "=d"(hi)); \
  x = ((unsigned long long)lo)|(((unsigned long long)hi)<<32); \
} while(0)

/* BIN2HEX
 * A problem in C is converting a variable-length binary string
 * into a character string containing hexidecimal representation
 * of each byte.  The size of the resultant string given input size n
 * is exactly 2n.  A version that allocates space and one that relies
 * on the user are both implemented.
 */

/* Initialization function for a 256-byte hex string table */
inline uint8_t bin2hex_init(char lt[256][2])
{
  uint16_t i;
  if(!lt) return 0;
  for(i=0;i<256;i++) {
    // Upper nibble
    //printf("Doing upper nibble for %u\n", i); fflush(stdout);
    switch(i>>4) {
      case 0x0: lt[i][0] = '0'; break;
      case 0x1: lt[i][0] = '1'; break;
      case 0x2: lt[i][0] = '2'; break;
      case 0x3: lt[i][0] = '3'; break;
      case 0x4: lt[i][0] = '4'; break;
      case 0x5: lt[i][0] = '5'; break;
      case 0x6: lt[i][0] = '6'; break;
      case 0x7: lt[i][0] = '7'; break;
      case 0x8: lt[i][0] = '8'; break;
      case 0x9: lt[i][0] = '9'; break;
      case 0xA: lt[i][0] = 'A'; break;
      case 0xB: lt[i][0] = 'B'; break;
      case 0xC: lt[i][0] = 'C'; break;
      case 0xD: lt[i][0] = 'D'; break;
      case 0xE: lt[i][0] = 'E'; break;
      case 0xF: lt[i][0] = 'F'; break;
    }

    // Lower nibble
    //printf("Doing lower nibble for %u\n", i); fflush(stdout);
    switch(i & 0x0F) {
      case 0x0: lt[i][1] = '0'; break;
      case 0x1: lt[i][1] = '1'; break;
      case 0x2: lt[i][1] = '2'; break;
      case 0x3: lt[i][1] = '3'; break;
      case 0x4: lt[i][1] = '4'; break;
      case 0x5: lt[i][1] = '5'; break;
      case 0x6: lt[i][1] = '6'; break;
      case 0x7: lt[i][1] = '7'; break;
      case 0x8: lt[i][1] = '8'; break;
      case 0x9: lt[i][1] = '9'; break;
      case 0xA: lt[i][1] = 'A'; break;
      case 0xB: lt[i][1] = 'B'; break;
      case 0xC: lt[i][1] = 'C'; break;
      case 0xD: lt[i][1] = 'D'; break;
      case 0xE: lt[i][1] = 'E'; break;
      case 0xF: lt[i][1] = 'F'; break;
    }
  }
  return 1;
}

/* Non-allocating */
/* Params are Lookup Table, destination, source, and size of INPUT data */
inline uint8_t bin2hex(char lt[256][2], char * destination, uint8_t * source, unsigned int size)
{
  unsigned int i = 0;
  unsigned int pos = 0;
  while(i < size) {
    destination[pos] = lt[source[i]][0];
    destination[pos+1] = lt[source[i]][1];
    i++, pos += 2;
  }
  return pos-1;
}

/* Allocating 
 * ONLY USE IF YOU'RE NOT LOOPING OVER THIS FUNCTION!
 */
/* Params are Lookup Table, destination, source, and size of INPUT data */
inline uint8_t abin2hex(char * destination, uint8_t * source, unsigned int size)
{
  unsigned int i = 0;
  unsigned int pos = 0;
  char lt[256][2];
  bin2hex_init(lt);
  while(i < size) {
    destination[pos] = lt[source[i]][0];
    destination[pos+1] = lt[source[i]][1];
    i++, pos += 2;
  }
  return pos-1;
}

/* ------------------------------------------------------------------- */
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
