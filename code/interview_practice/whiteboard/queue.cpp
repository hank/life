#include <cstdio>
#include <queue>
using namespace std;

int main() {
  queue<int> iqueue;
  iqueue.push(5);
  int f = iqueue.front();
  iqueue.pop();
  printf("%d\n", f);
  return 0;
}
