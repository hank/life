#include <cstdio>
#include <iostream>
#include "splay_tree.h"
int main()
{
  std::pair<int, int> p(5,4);
  splay_tree<int, int> st;
  st.insert(p);
  p = std::pair<int, int>(15,6);
  st.insert(p);
  p = std::pair<int, int>(55,7);
  st.insert(p);
  p = std::pair<int, int>(0,3);
  st.insert(p);
  p = std::pair<int, int>(2,2);
  st.insert(p);
  p = std::pair<int, int>(1,1);
  st.insert(p);
  
  st.print();
  int* foo = st.find(5);
  st.print();
  foo = st.find(5);
  if(foo) printf("Foo: %d\n", *foo);
  else puts("Uh, we didn't find 5.  Sorry for your loss.");
  return 0;
}
