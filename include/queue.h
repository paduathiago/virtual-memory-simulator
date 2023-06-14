#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    unsigned** items;
    int front;
    int rear;
    int maxSize;
};

struct Queue* createQueue(int maxSize);
int isQueueEmpty(struct Queue* queue);
int isQueueFull(struct Queue* queue);
int isInQueue(struct Queue* queue, unsigned item);
void enqueue(struct Queue* queue, unsigned item);
void* dequeue(struct Queue* queue);
void destroyQueue(struct Queue* queue);

#endif /* QUEUE_H */
