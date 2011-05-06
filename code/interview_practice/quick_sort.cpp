#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
using namespace std;

// Pick a random pivot
// Sort on each side of the pivot
int partition(int a[], int lo, int hi)
{
    // Static pivot
    int piv = a[lo];
    printf("Pivot: %d\n", piv);
    int q = hi+1, r = lo-1, h;
    for(;;)
    {
        // Move down
        do {
          --q;
        } while(a[q] > piv);
        // Move up
        do {
            ++r;
        } while(a[r] < piv);
        // Swap
        if(r < q) {
            cout << "Swapping: " << a[q] << " and " << a[r] << endl;
            h = a[r]; a[r] = a[q]; a[q] = h;
            for(int i=0; i<17; ++i) cout << a[i] << " ";
            cout << endl;
        }
        else {
            cout << "Returning: " << q << endl;
            return q;
        }
    }
}
// Recurse
void qs(int a[], int lo, int hi)
{
    if(lo < hi)
    {
        int piv = partition(a, lo, hi);
        qs(a, lo, piv);
        qs(a, piv+1, hi);
    }
}

int main()
{
    int a[] = {34,34,5,46,5,2,23,5,-3,32,2,54,53,32432,34,322,3};
    //int a[] = {300,6,2,6,46,-2,45,3};
    for(int i=0; i<17; ++i) cout << a[i] << " ";
    cout << endl;
    qs(a, 0, 16);
}
