// Basic priority queue using a heap
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "basic_heap.h"

void pq_swap(prio_q* pq, int a, int b)
{
   int s = pq->q[b]; 
   pq->q[b] = pq->q[a];
   pq->q[a] = s;
}

// Simply insert in the next available spot in the heap
int pq_insert(prio_q* pq, int val)
{
    if(pq->n == PQ_SIZE) return -1;
    pq->q[pq->n] = val;
    pq_bubble_up(pq, pq->n);
    return pq->n++;
}

int pq_parent(int val)
{
    switch(val)
    {
        case 0: return -1; break;
        default: return val/2; break;
    }
}

int pq_left_child(int val)
{
    return (2*val);
}

int pq_right_child(int val)
{
    return (2*val)+1;
}

// Find parents and swap if necessary
void pq_bubble_up(prio_q* pq, int val)
{
    // Start with given node and its parent
    int p = pq_parent(val);
    if(p == -1) return;
    // Swap if needed
    if(pq->q[p] < pq->q[val])
    {
        pq_swap(pq, p, val);
        // Move to next pair
        pq_bubble_up(pq, p);
    }
}

// Float an element down its subtree
int pq_bubble_down(prio_q* pq, int val)
{
    // Start with given node and its parent
    int l = pq_left_child(val);
    int r = pq_right_child(val);
    int m = val;

    if(l <= pq->n && pq->q[l] > pq->q[m]) m = l;
    if(r <= pq->n && pq->q[r] > pq->q[m]) m = r;
    if(m != val) 
    {
        pq_swap(pq, m, val);
        pq_bubble_down(pq, m);
    }
    return 0;
}

// Return the top of the queue
int pq_dequeue(prio_q* pq)
{
    int n = pq_delete(pq, 0);
    return n;
}

// Delete the given element and rebalance its subtree
int pq_delete(prio_q* pq, int el)
{
    if(pq->n == 0) return -1;
    // Save the head
    int p = pq->q[el];
    // Put the rightmost leaf in its place and bubble down
    pq->q[el] = pq->q[pq->n - 1];
    pq->n--;
    pq_bubble_down(pq, el);
    return p;
}

// Run through all the elements in the queue in order
void pq_run(prio_q* pq)
{
    int i = pq->n;
    int p;
    while(i--)
    {
        p = pq_dequeue(pq);
        printf("%d ", p);
    }
    printf("\n");
}

void pq_print_tree(prio_q* pq)
{
    int i, k, m;
    int j = 1;
    if(pq->n < 1) return;
    // Figure number of spaces to indent, should be ~= log2(pq->n)
    int num_spaces = (int)log2((double)pq->n) + 5;
    k = num_spaces;
    while(k--) printf("%c", ' ');
    for(i=0; i < pq->n; ++i)
    {
        printf("%d", pq->q[i]);
        m = num_spaces + 1;
        while(m--) printf("%c", ' ');
        if(i + 1 == j) 
        {
            j *= 2;
            j += 1;
            printf("\n");
            num_spaces /= 2;
            k = num_spaces;
            while(k--) printf("%c", ' ');
        }
    }
    printf("\n");
}

// Sort a list
void heapsort(int s[], int i)
{
    prio_q* pq = calloc(1,sizeof(prio_q));
    int j;
    // Insert them all in a heap
    for(j=0; j<i; ++j)
    {
        pq_insert(pq, s[j]);
    }
    pq_print_tree(pq);
    // Now replace them in the original array
    for(j=0; j<i; ++j)
    {
        s[j] = pq_dequeue(pq);
    }
    free(pq);
}

int main()
{
    prio_q* pq = calloc(1,sizeof(prio_q));
    printf("%u elements inserted.\n", pq->n);
    pq_insert(pq, 5);
    pq_insert(pq, 50);
    pq_insert(pq, 60);
    pq_insert(pq, 70);
    pq_insert(pq, 80);
    pq_insert(pq, 90);
    pq_insert(pq, 342);
    pq_insert(pq, 3);
    printf("%u elements inserted.\n", pq->n);
    pq_print_tree(pq);

    printf("Trying to dequeue..\n");
    int foo = pq_dequeue(pq);
    printf("Got %d..\n", foo);
    pq_print_tree(pq);

    printf("Trying to run through..\n");
    pq_run(pq);
    int a[5] = {4543,-33,4,54,2};
    printf("Original: ");
    int j = 0;
    for(; j < 5; ++j) printf("%d ", a[j]);
    printf("\n");
    heapsort(a, 5);
    printf("Heapsorted: ");
    for(j=0; j < 5; ++j) printf("%d ", a[j]);
    printf("\n");
    free(pq);
    return 0;
}
