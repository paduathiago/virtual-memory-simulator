#include "circular_queue.h"

CircularQueue* createCircularQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->buffer = (int*)malloc(capacity * sizeof(int));
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

void enqueue(CircularQueue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->buffer[queue->rear] = item;
    queue->size++;
}

int dequeue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("A fila está vazia. Não é possível desenfileirar elementos.\n");
        return -1; // Valor inválido
    }

    int item = queue->buffer[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    if (isEmpty(queue))
        queue->front = queue->rear = -1;

    return item;
}

int front(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("A fila está vazia. Não há elementos no início.\n");
        return -1; // Valor inválido
    }

    return queue->buffer[queue->front];
}

int rear(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("A fila está vazia. Não há elementos no final.\n");
        return -1; // Valor inválido
    }

    return queue->buffer[queue->rear];
}

void destroyCircularQueue(CircularQueue* queue) {
    free(queue->buffer);
    free(queue);
}