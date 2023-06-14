#ifndef DOUBLY_LINKED_STACK_H
#define DOUBLY_LINKED_STACK_H

struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
};

struct DoublyLinkedStack {
    struct Node* top;
    struct Node* bottom;
};

struct DoublyLinkedStack* createDoublyLinkedStack();
int isDLStackEmpty(struct DoublyLinkedStack* stack);
void push(struct DoublyLinkedStack* stack, void* data);
void* pop(struct DoublyLinkedStack* stack);
void destroyDLStack(struct DoublyLinkedStack* stack);

#endif /* DOUBLY_LINKED_STACK_H */
