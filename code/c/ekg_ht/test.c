/* Slist
 * by Erik Gregg
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <openssl/md5.h>
#include "ekg_ht.h"

static inline u_char * md5(char * buf, uint32_t len)
{
  if(len == 0) len = strlen(buf);
  u_char * digest;
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, buf, len);
  MD5_Final(digest, &ctx);
  return digest;
}

int main() {
  u_char * md5sum = md5("omg", 0);
  uint32_t * mdptr = (uint32_t *)md5sum;
  printf("%x%x%x%x\n", *mdptr, *(mdptr+1), *(mdptr+2), *(mdptr+3));
  free(md5sum);
  return EXIT_SUCCESS;
}
