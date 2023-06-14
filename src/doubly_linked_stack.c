#include "doubly_linked_stack.h"

struct DoublyLinkedStack* createDoublyLinkedStack(int maxSize) {
    struct DoublyLinkedStack* stack = (struct DoublyLinkedStack*)malloc(sizeof(struct DoublyLinkedStack));
    stack->top = NULL;
    stack->bottom = NULL;
    stack->maxSize = maxSize;
    stack->size = 0;
    return stack;
}

int isDLStackEmpty(struct DoublyLinkedStack* stack) {
    return stack->top == NULL;
}

int isDLStackFull(struct DoublyLinkedStack* stack) {
    return stack->size == stack->maxSize;
}

int isinDLStack(struct DoublyLinkedStack* stack, void* data) 
{
    struct Node* currentNode = stack->top;
    while (currentNode != NULL) {
        if (currentNode->data == data)
            return 1;
        currentNode = currentNode->prev;
    }
    return 0;
}

void push(struct DoublyLinkedStack* stack, void* data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = stack->top;
    newNode->next = NULL;

    if (stack->top != NULL) 
        stack->top->next = newNode;
    else 
        stack->bottom = newNode;

    stack->top = newNode;
    stack->size++;
}

void* popBottom(struct DoublyLinkedStack* stack) 
{
    if (isDoublyLinkedStackEmpty(stack)) {
        printf("A pilha está vazia, impossível remover elemento.\n");
        return NULL;
    }

    struct Node* bottomNode = stack->bottom;
    void* bottomData = bottomNode->data;

    stack->bottom = bottomNode->next;
    if (stack->bottom != NULL) 
        stack->bottom->prev = NULL;
    else 
        stack->top = NULL;

    free(bottomNode);
    stack->size--;
    return bottomData;
}

void destroyDLStack(struct DoublyLinkedStack* stack) {
    while (!isDoublyLinkedStackEmpty(stack)) 
        pop(stack);

    free(stack);
}