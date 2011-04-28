#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct _lnode {
    struct _lnode* next;
    int data;
} lnode;

typedef struct {
    struct _lnode* head;
    struct _lnode* tail;
    int size;
} list;

void insert(list* l, int item)
{
    // Initialize if needed
    if(!l->tail) l->tail = l->head = calloc(1,sizeof(lnode));
    else 
    {
        l->tail->next = calloc(1,sizeof(lnode));
        l->tail = l->tail->next;
    }
    l->tail->data = item;
    l->size++;
}

void print_list(list* l)
{
    lnode* ln = l->head;
    while(ln)
    {
        printf("%d\n", ln->data);
        ln = ln->next;
    }
}

void list_free(list* l)
{
    lnode* ln = l->head, *t;
    while(ln)
    {
        t = ln->next;
        free(ln);
        ln = t;
    }
}

void ms(lnode* b, lnode* e, int size)
{
    if(size == 2)
    {
        // Normal final case, swap if needed
        //if(b->)
    }
    else
    {
        // Split, recurse
        int 
    }
}

int main()
{
    list* l = calloc(1,sizeof(list));
    insert(l, 4);
    insert(l, 7);
    insert(l, -17);
    insert(l, 45);
    insert(l, 923);
    print_list(l);

    // Merge sort the list
    ms(l->head, l->tail, l->size);

    list_free(l);
    free(l);
    return 0;
}
