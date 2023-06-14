#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
    int* items;
    int front;
    int rear;
    int maxSize;
};

struct Queue* createQueue(int maxSize);
int isEmpty(struct Queue* queue);
int isFull(struct Queue* queue);
void addItem(struct Queue* queue, int item);
int removeItem(struct Queue* queue);
void destroyQueue(struct Queue* queue);

#endif /* QUEUE_H */
