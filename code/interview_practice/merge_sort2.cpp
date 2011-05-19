#include <iostream>
#include <queue>
using namespace std;

void merge(int a[], int low, int middle, int high)
{
  cout << "Merge: " << low << " " << middle << " " << high << endl;
  queue<int> v1, v2;
  for(int i=low; i <= middle; ++i) v1.push(a[i]);
  for(int i=middle+1; i <= high; ++i) v2.push(a[i]);

  int i = low;
  while(!v1.empty() && !v2.empty())
  {
    if(v1.front() <= v2.front())
    {
      a[i++] = v1.front();
      v1.pop();
    }
    else
    {
      a[i++] = v2.front();
      v2.pop();
    }
  }
  // Finalize any remnants
  while(!v1.empty())
  {
    a[i++] = v1.front();
    v1.pop();
  }
  while(!v2.empty())
  {
    a[i++] = v2.front();
    v2.pop();
  }
}

void ms(int a[], int low, int high)
{
  cout << "MS: " << low << " " << high << endl;
  if(low < high)
  {
    cout << "recursing" << endl;
    // Find the middle and recurse
    int middle = (high+low)/2;
    ms(a, low, middle);
    ms(a, middle+1, high);
    merge(a, low, middle, high);
  }
}

int main()
{
  int a[10] = {2,3,4,65,2,4,2,23,42,3};
  for(int i=0; i<10; ++i) cout << a[i] << " ";
  cout << endl;
  ms(a, 0, 9);
  for(int i=0; i<10; ++i) cout << a[i] << " ";
  cout << endl;
  return 0;
}
