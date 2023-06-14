#ifndef DOUBLY_LINKED_STACK_H
#define DOUBLY_LINKED_STACK_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
};

struct DoublyLinkedStack {
    struct Node* top;
    struct Node* bottom;
    int maxSize;
    int size;
};

struct DoublyLinkedStack* createDLStack(int maxSize);
int isDLStackEmpty(struct DoublyLinkedStack* stack);
int isDLStackFull(struct DoublyLinkedStack* stack);
int isinDLStack(struct DoublyLinkedStack* stack, void* data);
void push(struct DoublyLinkedStack* stack, void* data);
void* popBottom(struct DoublyLinkedStack* stack);
void* popFromData(struct DoublyLinkedStack* stack, void* data);
void destroyDLStack(struct DoublyLinkedStack* stack);

#endif /* DOUBLY_LINKED_STACK_H */
