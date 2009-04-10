#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ekg_sys.h"

int main(int argc, char ** argv) {
  char * buf, * buf2;
  uint32_t buflen, failure = 0, i;
  unsigned int x,y;
  unsigned int speed[3];

  if(argc < 2) {
    // No input num, just use 1000
    buflen = 1000;
  } else {
    buflen = atoi(argv[1]);
    if(buflen == 0) return 0;
  }

  if(!(buf = malloc(buflen))) {
    printf("Couldn't allocate memory.\n");
    return 0;
  }
  printf("Allocated %u bytes\n", buflen);

  if(!(buf2 = malloc(buflen))) {
    printf("Couldn't allocate memory.\n");
    return 0;
  }
  printf("Allocated %u bytes\n", buflen);

  printf("Filling %u bytes with junk\n", buflen);
  for(i=0; i<buflen; i++) {
    buf[i] = buf2[i] = 1;
  }

  // TEST OF MEMCMP VS. FMEMCMP
  printf("***************** FMEMCMP *****************\n");

  printf("Running system memcmp: ");
  GET_CYCLES(x);
  if(memcmp(buf, buf2, buflen) != 0) failure = 1;
  GET_CYCLES(y);
  printf("time=%u, ", y-x);
  speed[0] = y-x;

  if(!failure) {
    printf("Match!\n");
  } else {
    printf("No Match!\n");
  }
  failure = 0;

  printf("Running forloop memcmp: ");
  GET_CYCLES(x);
  for(i=0; i<buflen; i++) {
    if(buf[i] != buf2[i]) failure = 1;
  }
  GET_CYCLES(y);
  printf("time=%u, ", y-x);
  speed[1] = y-x;

  if(!failure) {
    printf("Match!\n");
  } else {
    printf("No Match!\n");
  }
  failure = 0;

  printf("Running fmemcmp: ");
  GET_CYCLES(x);
  if((fmemcmp(buf, buf2, buflen)) != 0) failure = 1;
  GET_CYCLES(y);
  printf("time=%u, ", y-x);
  speed[2] = y-x;

  if(!failure) {
    printf("Match!\n");
  } else {
    printf("No Match! (%d)\n", failure);
  }
  failure = 0;


  // Summarize
  printf(":: fmemcmp is %g times faster than system memcmp.\n", ((float)speed[0])/speed[2]);
  printf(":: fmemcmp is %g times faster than forloop memcmp.\n", ((float)speed[1])/speed[2]);

  printf("***************** FMEMCMP *****************\n");

  return 1;
}
