#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* buffer;
    int capacity;
    int front;
    int rear;
    int size;
} CircularQueue;

CircularQueue* createCircularQueue(int capacity);
void destroyCircularQueue(CircularQueue* queue);
int isFull(CircularQueue* queue);
int isEmpty(CircularQueue* queue);
void enqueue(CircularQueue* queue, int item);
int dequeue(CircularQueue* queue);
int front(CircularQueue* queue);
int rear(CircularQueue* queue);

#endif