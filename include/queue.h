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

struct queue
{
    node_t* head;
    node_t* tail;
    int size;
    int capacity;
};


node_t* create_node();

queue_t* createQueue(int capacity);

int isQueueFull(queue_t* q);

int isInQueue(queue_t* q, long long val);

void pop_back(queue_t* q);

node_t* popFront(queue_t* q);
 
void pushBack(queue_t* q, long long val);

void push_front(queue_t* q, long long val);

node_t* find_node(queue_t* q, long long val);

void erase(queue_t* q, long long val);

void print_queue(queue_t* q);

void destroyQueue(queue_t* q);

#endif /* QUEUE_H */
