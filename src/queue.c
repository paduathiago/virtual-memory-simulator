#include "queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define dbg(x) printf(" %s : %lld ",#x,x)

node_t* create_node()
{
    node_t* n = (node_t*)malloc(sizeof(node_t));
    return n;
}

queue_t* createQueue(int capacity)
{
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->capacity = capacity;
    q->size = 0;
    return q;
}

int isQueueFull(queue_t* q){
    return q->size == q->capacity;
}

int isInQueue(queue_t* q, long long val)
{
    node_t* n = q->head;
    while(n != NULL){
        if(n->value == val)
            return 1;
        n = n->nxt;
    }
    return 0;
}

node_t* popFront(queue_t* q) 
{
    if (q->head == NULL)
        return NULL;

    node_t* removed_node = q->head;

    if (q->head == q->tail) 
    {
        q->tail = NULL;
        q->head = NULL;
    } 
    else 
    {
        node_t* new_head = q->head->nxt;
        new_head->prev = NULL;
        q->head = new_head;
    }
    q->size--;
    return removed_node;
}
 
void pushBack(queue_t* q, long long val)
{
    node_t* new_tail = create_node();
    new_tail->value = val;
    new_tail->prev = q->tail;
    new_tail->nxt = NULL;

    if(q->head == NULL)
    {
        q->head = new_tail;
        q->tail = new_tail;
        q->size++;
        return;
    }

    q->tail->nxt = new_tail;
    q->tail = new_tail;
    q-> size++;
}

void destroyQueue(queue_t* q){
    node_t* n = q->head;
    while(n != NULL){
        node_t* nxt = n->nxt;
        free(n);
        n = nxt;
    }
    free(q);
}
