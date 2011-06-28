#include <cstdio>
#include <queue>
using namespace std;

void radix_internal(queue<int>* qs, int qn, int* a, int n, 
                    int mask, int shift) 
{
  for(int i=0; i<n; ++i) {
    // Sign extension doesn't end up being a problem since we're masking
    qs[(a[i] >> shift) & mask].push(a[i]);
  }
  int* last = a;
  for(int i=0; i<qn; ++i) {
    while(!qs[i].empty()) {
      *last = qs[i].front();
      qs[i].pop();
      ++last;
    }
  }
}

void radix_sort(int* a, int n)
{
  queue<int> qs[256];
  radix_internal(qs, 256, a, n, 0xFF, 0);
  radix_internal(qs, 256, a, n, 0xFF, 8);
  radix_internal(qs, 256, a, n, 0xFF, 16);
  radix_internal(qs, 256, a, n, 0xFF, 24);
}

void radix_sort_16bit(int* a, int n)
{
  queue<int>* qs = new queue<int>[65536];
  radix_internal(qs, 65536, a, n, 0xFFFF,  0);
  radix_internal(qs, 65536, a, n, 0xFFFF,  16);
}

int main() {
  int a[] = {3,34,24,5,4356,34,32423,423,4543,32,432,423,354,354};
  int b[] = {3,34,24,5,4356,34,32423,423,4543,32,432,423,354,354};
  int n = sizeof(a) / sizeof(a[0]);
  radix_sort(a,n);
  for(int i=0; i < n; ++i) {
    printf("%d\n", a[i]);
  }
  radix_sort_16bit(b,n);
  for(int i=0; i < n; ++i) {
    printf("%d\n", b[i]);
  }
  return 0;
}
