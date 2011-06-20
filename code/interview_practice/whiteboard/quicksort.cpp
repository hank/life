#include <list>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

template<class T>
list<T> quicksort(const list<T>& t) {
  if(t.size() <= 1) return t;
  const T& pivot = t.front();
  list<T> a1, a2, v;
  typename list<T>::const_iterator it = t.begin();
  ++it;
  while(it != t.end()) {
    if(*it > pivot) a2.push_back(*it);
    else if(*it < pivot) a1.push_back(*it);
    else v.push_back(*it);
    ++it;
  }

  a1 = quicksort(a1);
  a1.push_back(pivot);
  a1.insert(a1.end(), v.begin(), v.end());
  a2 = quicksort(a2);
  a1.insert(a1.end(), a2.begin(), a2.end());
  return a1;
}

template<class T>
vector<T> quicksort(const vector<T>& t) {
  if(t.size() <= 1) return t;
  //const T& pivot = t.front(); // Lame Implementation
  const T& pivot = t[rand() % t.size()];
  vector<T> a1, a2, v;
  typename vector<T>::const_iterator it = t.begin();
  while(it != t.end()) {
    if(&pivot != &(*it)) {
      if(*it > pivot) a2.push_back(*it);
      else if(*it < pivot) a1.push_back(*it);
      else v.push_back(*it);
    }
    ++it;
  }
  
  a1 = quicksort(a1);
  a1.push_back(pivot);
  a1.insert(a1.end(), v.begin(), v.end());
  a2 = quicksort(a2);
  a1.insert(a1.end(), a2.begin(), a2.end());
  return a1;
}

int main()
{
  srand(time(0));
  list<int> i;
  vector<int> j;
  i.push_back(4);
  i.push_back(2321);
  i.push_back(1);
  i.push_back(3423);
  i.push_back(2);
  i.push_back(45);
  i.push_back(6);
  i.push_back(24);
  i.push_back(24);
  i.push_back(24);
  i.push_back(24);
  i.push_back(54);
  i.push_back(34);
  i.push_back(874);
  i.push_back(24);
  j.push_back(4);
  j.push_back(2321);
  j.push_back(1);
  j.push_back(3423);
  j.push_back(2);
  j.push_back(45);
  j.push_back(6);
  j.push_back(24);
  j.push_back(24);
  j.push_back(24);
  j.push_back(24);
  j.push_back(54);
  j.push_back(34);
  j.push_back(874);
  j.push_back(24);
  list<int> k = quicksort(i);
  list<int>::const_iterator it = k.begin();
  while(it != k.end()) {
    printf("%d ", *it);
    ++it;
  }
  puts("\n");
  vector<int> l = quicksort(j);
  vector<int>::const_iterator it2 = l.begin();
  while(it2 != l.end()) {
    printf("%d ", *it2);
    ++it2;
  }
  puts("\n");
  return 0;
}
