#include <stdio.h>
#include <stdlib.h>
void itoa(int i, char* buf) {
  int count = 0;
  if(i < 0) {
    buf[0] = '-';
    ++buf;
    i *= -1;
  }
  int j = i;
  do {
    ++count;
    j /= 10;
  } while(j > 0);
  // Null Terminate
  buf[count] = 0;
  while(count > 0) {
    buf[count - 1] = (i % 10) + 0x30;
    i /= 10;
    --count;
  }
}

int main() {
  int a = -3423432;
  char * buf = calloc(1, 50);
  itoa(a, buf);
  printf("%s\n", buf);
  return 0;
}
