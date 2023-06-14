#include "queue.h"

struct Queue* createQueue(int maxSize) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->items = (void**)malloc(sizeof(void*) * maxSize);
    queue->front = -1;
    queue->rear = -1;
    queue->maxSize = maxSize;
    return queue;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front == -1;
}

int isQueueFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->maxSize == queue->front;
}

int isInQueue(struct Queue* queue, unsigned item) {
    int i;
    for (i = queue->front; i != queue->rear; i = (i + 1) % queue->maxSize)
    {
        if (queue->items[i] == item)
            return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue, unsigned item) {
    if (isQueueEmpty(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % queue->maxSize;
    queue->items[queue->rear] = item;
    printf("Elemento adicionado à fila.\n");
}

void* dequeue(struct Queue* queue) {
    void* item;
    if (isQueueEmpty(queue)) {
        printf("Fila vazia, impossível remover elemento.\n");
        return NULL;
    } else {
        item = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        } 
        else 
            queue->front = (queue->front + 1) % queue->maxSize;
        
        return item;
    }
}

void destroyQueue(struct Queue* queue) {
    free(queue->items);
    free(queue);
}