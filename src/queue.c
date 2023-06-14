#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue* createQueue(int maxSize) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->items = (int*)malloc(sizeof(int) * maxSize);
    queue->front = -1;
    queue->rear = -1;
    queue->maxSize = maxSize;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

int isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->maxSize == queue->front;
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Fila cheia, impossível adicionar elemento.\n");
    } else {
        if (isEmpty(queue)) {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % queue->maxSize;
        queue->items[queue->rear] = item;
        printf("Elemento %d adicionado à fila.\n", item);
    }
}

int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Fila vazia, impossível remover elemento.\n");
        return -1;
    } else {
        item = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->maxSize;
        }
        return item;
    }
}

void destroyQueue(struct Queue* queue) {
    free(queue->items);
    free(queue);
}