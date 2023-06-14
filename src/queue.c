#include "queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define dbg(x) printf(" %s : %lld ",#x,x)

node_t* create_node(){
    node_t* n = (node_t*)malloc(sizeof(node_t));
    return n;
}

queue_t* create_queue(){
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    return q;
}

void pop_back(queue_t* q){
    if(q->head == NULL)
        return;
    if(q->head == q->tail){
        free(q->head);
        q->tail = NULL;
        q->head = NULL;
    } else{
        node_t* new_tail = q->tail->prev;
        free(q->tail);
        new_tail->nxt = NULL;
        q->tail = new_tail;
    }
}

void pop_front(queue_t* q){
    if(q->head == NULL)
        return;
    if(q->head == q->tail){
        free(q->head);
        q->tail = NULL;
        q->head = NULL;
    } else{
        node_t* new_head = q->head->nxt;
        free(q->head);
        new_head->prev = NULL;
        q->head = new_head;
    }
}
 
void push_back(queue_t* q, long long val){
    //dbg(val);
    node_t* new_tail = create_node();
    new_tail->value = val;
    new_tail->prev = q->tail;
    new_tail->nxt = NULL;

    if(q->head == NULL){
        q->head = new_tail;
        q->tail = new_tail;
        return;
    }

    q->tail->nxt = new_tail;
    q->tail = new_tail;
}

void push_front(queue_t* q, long long val){
    node_t* new_head = create_node();
    new_head->value = val;
    new_head->prev = NULL;
    new_head->nxt = q->head;

    if(q->head == NULL){
        q->head = new_head;
        q->tail = new_head;
        return;
    }

    q->head->prev = new_head;
    q->head = new_head;
}

node_t* find_node(queue_t* q, long long val){
    node_t* n = q->head;
    while(n != NULL && n->value != val)
        n = n->nxt;
    return n;
}

void erase(queue_t* q, long long val){
    node_t* n = find_node(q,val);
    if(n == NULL)
        return;
    n->prev->nxt = n->nxt;
    n->nxt->prev = n->prev;
    free(n);
}

void print_queue(queue_t* q){
    node_t* n = q->head;
    while(n != NULL){
        printf("%lld ", n->value);
        n = n->nxt;
    }
    printf("\n");
}
