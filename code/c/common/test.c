#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ekg_sys.h"

#define CRAZY_SIZE (1<<10)

int bin2hex_main(int argc, char ** argv) {
  char lt[256][2];
  unsigned int x,y;
  union {
    uint32_t u32;
    uint8_t u8[4];
  } random_num;
  uint16_t i;
  printf("***************** BIN2HEX *****************\n");

  if(bin2hex_init(lt) == 0) {
    // Fail.. Leave
    return 0;
  }

  printf("Table created: \n");
  for(i=0; i<256; i++) {
    printf("%c%c", lt[i][0], lt[i][1]);
    if(i%15 == 0) printf("\n");
    else printf(" ");
  }

  // Initialize crazy binary array
  uint8_t * crazy_hex = malloc(CRAZY_SIZE);
  for(i=0; i<CRAZY_SIZE-3; i++) {
    random_num.u32 = rand();
    crazy_hex[i] = random_num.u8[0];
    crazy_hex[i+1] = random_num.u8[1];
    crazy_hex[i+2] = random_num.u8[2];
    crazy_hex[i+3] = random_num.u8[3];
    i += 4;
  }
  char hex_dest[2 + 2*CRAZY_SIZE]; 
  hex_dest[0] = '0';
  hex_dest[1] = 'x';
  GET_CYCLES(x);
  bin2hex(lt, &hex_dest[2], crazy_hex, CRAZY_SIZE);
  GET_CYCLES(y);
  printf("time=%u, ", y-x);
  printf("Output: %.*s\n", 2 + 2*CRAZY_SIZE, hex_dest);
  printf("***************** BIN2HEX *****************\n");

  return 1;
}

int fmemcmp_main(int argc, char ** argv) {
  char * buf, * buf2;
  uint32_t buflen, failure = 0, i;
  unsigned int x,y;
  unsigned int speed[3];

  if(argc < 2) {
    // No input num, just use 1000
    buflen = 1000000;
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

int main(int argc, char ** argv) {
  //fmemcmp_main(argc, argv);
  bin2hex_main(argc, argv);
}
