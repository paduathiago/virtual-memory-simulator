#include "circular_queue.h"

CircularQueue* createCircularQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->buffer = (PageTableEntry*)malloc(capacity * sizeof(PageTableEntry));
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

int isFull(CircularQueue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(CircularQueue* queue) {
    return queue->size == 0;
}

void enqueue(CircularQueue* queue, int item, char mode) {
    PageTableEntry * newPage = createPageTableEntry(item, mode);
    
    if (isEmpty(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->buffer[queue->rear] = *newPage;
    queue->size++;
}

int itemReplacement(CircularQueue* queue, int newItem, char mode) // TESTAR
{
    PageTableEntry * newPage = createPageTableEntry(newItem, mode);
    while (queue->buffer[queue->clockPointer].referenceBit == 1)
    {
        queue->buffer[queue->clockPointer].referenceBit = 0;
        queue->clockPointer = (queue->clockPointer + 1) % queue->capacity;
        if(queue->buffer[queue->clockPointer].referenceBit == 0)
        {
            int replaced = queue->buffer[queue->clockPointer].pageNumber;
            queue->buffer[queue->clockPointer] = *newPage;
            return replaced;
        }
    }
    return -1;
}

void destroyCircularQueue(CircularQueue* queue) {
    free(queue->buffer);
    free(queue);
}