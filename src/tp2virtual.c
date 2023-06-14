#include <stdio.h>

#include "doubly_linked_stack.h"
#include "queue.h"

int sValue(int pageSize)
{
    int tmp = pageSize;
    int s = 0;
    while (tmp > 1) 
    {
        tmp = tmp >> 1;
        s++;
    }
    return s;
}

int main(int argc, char *argv[])
{
    char * algorithm = argv[1];
    char * fileName = argv[2];
    unsigned pageSize = atoi(argv[3]);
    unsigned memorySize = atoi(argv[4]);

    unsigned s = sValue(pageSize);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) 
    {
        printf("Invalid File!.\n");
        return 1;
    }

    if (argc != 5)
    {
        printf("Error: Invalid arguments\n");
        return 1;
    }

    if (algorithm == '2a')
    {

    }
    else if (algorithm == 'fifo')
    {
        unsigned addr, page;
        char mode;

        // The queue size is equivalent to the memory size divided by the page size. This represents the number of pages in memory
        struct Queue * queue = createQueue(memorySize/pageSize);  
        while (fscanf(file, "%8s %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            // Verificar se a página já está na memória
            if(!isInQueue(queue, page))
            {
                // Se não estiver, verificar se a memória está cheia.
                if (isQueueFull(queue))
                {
                    // Se estiver, desenfileirar a página mais antiga.
                    dequeue(queue);
                    // Essa página se torna suja?
                }
                
                // Chamar método para enfileirar a página.
                enqueue(queue, page);
            }  
        }
        destroyQueue(queue);
        fclose(file);
    }
    else if (algorithm == 'lru')
    {
        unsigned addr, page;
        char mode;

        struct DoublyLinkedStack * stack = createDLStack(memorySize/pageSize);  
        while (fscanf(file, "%8s %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            // Verificar se a página já está na memória
            if(!isInDLStack(stack, page))
            {
                // Se não estiver, verificar se a memória está cheia.
                if (isDLStackFull(stack))
                {
                    // Se estiver, desenfileirar a página no fundo da pilha.

                    // Essa página se torna suja?
                }
                
                // Chamar método para adicionar a página.
                pushDLStack(stack, page);
            }
        }
        destroyDLStack(stack);
    }
    else if (algorithm == 'random')
    {

    }
    else
    {
        printf("Error: Invalid algorithm\n");
        return 1;
    }

    return 0;
}