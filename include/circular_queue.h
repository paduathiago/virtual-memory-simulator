#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "page_table.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    PageTableEntry* buffer;
    int capacity;
    int front;
    int rear;
    int size;
    int clockPointer;
} CircularQueue;

CircularQueue* createCircularQueue(int capacity);
void destroyCircularQueue(CircularQueue* queue);
int isFull(CircularQueue* queue);
int isEmpty(CircularQueue* queue);
void enqueue(CircularQueue* queue, int item);
PageTableEntry dequeue(CircularQueue* queue);
PageTableEntry front(CircularQueue* queue);
PageTableEntry rear(CircularQueue* queue);

#endif
