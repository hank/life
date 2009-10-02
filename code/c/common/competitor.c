#include <stdio.h>
#include <stdlib.h>

char* char_to_hex( const unsigned char* p_array, unsigned int p_array_len, char** hex2ascii) {
    unsigned char* str = malloc(p_array_len*2+1);
    const unsigned char* p_end = p_array + p_array_len;
    size_t pos=0;
    const unsigned char* p;
    for( p = p_array; p != p_end; p++, pos+=2 ) {
       str[pos] = hex2ascii[*p][0];
       str[pos+1] = hex2ascii[*p][1];
    }
    return (char*)str;
}

int competitor_main() {
  size_t hex2ascii_len = 256;
  char** hex2ascii;
  int i;
  hex2ascii = malloc(hex2ascii_len*sizeof(char*));
  for(i=0; i<hex2ascii_len; i++) {
    hex2ascii[i] = malloc(3*sizeof(char));
    snprintf(hex2ascii[i], 3,"%02X", i);
  }
  size_t len = 8;
  const unsigned char a[] = "DO NOT WANT";
  printf("%s\n", char_to_hex((const unsigned char*)a, len, (char**)hex2ascii));
}
