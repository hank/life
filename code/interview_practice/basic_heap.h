// Basic heap
#define PQ_SIZE 64

// Heap structures
typedef struct {
    int q[PQ_SIZE + 1];
    int n;
} prio_q;

void pq_swap(prio_q* pq, int a, int b);
int pq_insert(prio_q* pq, int val);
int pq_parent(int val);
int pq_left_child(int val);
int pq_right_child(int val);
int pq_bubble_down(prio_q* pq, int val);
int pq_dequeue(prio_q* pq);
int pq_delete(prio_q* pq, int el);
void pq_run(prio_q* pq);
void pq_print_tree(prio_q* pq);
void pq_bubble_up(prio_q* pq, int val);
