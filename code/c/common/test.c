#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ekg_sys.h"
#include "competitor.h"

#define CRAZY_SIZE (1<<10)

int bin2hex_main(int argc, char ** argv) {
  FILE * rand_fh;
  char lt[256][2];
  unsigned int x,y;
  char * newhex_dest;
  union {
    uint32_t u32;
    uint8_t u8[4];
  } random_num;
  uint16_t i;
  printf("***************** BIN2HEX *****************\n");

  if(bin2hex_init(lt) == 0) {
    // Fail.. Leave
    fprintf(stderr, "Unable to init lookup table.\n");
    return EXIT_FAILURE;
  }

  rand_fh = fopen("/dev/urandom", "r");
  if(!rand_fh) {
    fprintf(stderr, "Unable to open random buffer.\n");
    return EXIT_FAILURE;
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
    if((fread(&random_num.u32, 4, 1, rand_fh) == 0)) {
      fprintf(stderr, "Could not read 4 bytes from file.\n");
      return EXIT_FAILURE;
    }
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
  printf("***************** BIN2HEX Competition *****************\n");

  size_t hex2ascii_len = 256;
  char** hex2ascii;
  hex2ascii = malloc(hex2ascii_len*sizeof(char*));
  for(i=0; i<hex2ascii_len; i++) {
    hex2ascii[i] = malloc(3*sizeof(char));
    snprintf(hex2ascii[i], 3,"%02X", i);
  }
  size_t len = 8;
  GET_CYCLES(x);
  newhex_dest = char_to_hex((const unsigned char*)crazy_hex, CRAZY_SIZE, (char**)hex2ascii);
  GET_CYCLES(y);
  printf("time=%u, ", y-x);
  printf("Output: 0x%s\n", newhex_dest);

  fclose(rand_fh);

  return EXIT_SUCCESS;
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
    if(buflen == 0) return EXIT_FAILURE;
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

  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  //fmemcmp_main(argc, argv);
  bin2hex_main(argc, argv);
}
