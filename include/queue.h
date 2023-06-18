#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define queue_t struct queue
#define node_t struct node


struct node{
    node_t* prev;
    node_t* nxt;
    long long value;
};

node_t* create_node();

struct queue
{
    node_t* head;
    node_t* tail;
    int size;
    int capacity;
};

queue_t* createQueue(int capacity);

int isQueueFull(queue_t* q);

int isInQueue(queue_t* q, long long val);

node_t* popFront(queue_t* q);
 
void pushBack(queue_t* q, long long val);

void destroyQueue(queue_t* q);

#endif /* QUEUE_H */
