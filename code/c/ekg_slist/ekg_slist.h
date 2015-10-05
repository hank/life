/* Slist
 * by Erik Gregg
 */
#ifndef __EKG_SLIST__
#define __EKG_SLIST__
#include <stdio.h>
#include <stdint.h>

typedef struct _snode_t snode_t;
struct _snode_t
{
    snode_t* next;
    uint32_t data;
};

typedef struct
{
    snode_t* head;
    snode_t* tail;
    char* name;
} slist_t;

slist_t* slist_init();
snode_t* slist_push(slist_t* list, snode_t* node);
uint32_t slist_print(slist_t* list);
slist_t* slist_reverse(slist_t* list);

#endif
