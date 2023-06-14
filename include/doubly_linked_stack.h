#ifndef DOUBLY_LINKED_STACK_H
#define DOUBLY_LINKED_STACK_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    unsigned data;
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
int isinDLStack(struct DoublyLinkedStack* stack, unsigned data);
void push(struct DoublyLinkedStack* stack, unsigned data);
unsigned popBottom(struct DoublyLinkedStack* stack);
unsigned popFromData(struct DoublyLinkedStack* stack, unsigned data);
void destroyDLStack(struct DoublyLinkedStack* stack);

#endif /* DOUBLY_LINKED_STACK_H */
