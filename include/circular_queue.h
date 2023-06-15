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
int isFull(CircularQueue* queue);
int isEmpty(CircularQueue* queue);
void enqueue(CircularQueue* queue, int item, char mode);
int itemReplacement(CircularQueue* queue, int newItem, char mode);
void destroyCircularQueue(CircularQueue* queue);

#endif
