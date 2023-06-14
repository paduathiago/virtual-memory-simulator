#include <stdio.h>

#include "circular_queue.h"
#include "doubly_linked_stack.h"
#include "page_table.h"
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
    PageTable* pgTable = createPageTable(memorySize/pageSize);

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
        unsigned addr, page;
        char mode;

        while (fscanf(file, "%8s %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            
            CircularQueue * circularQ = createCircularQueue(pgTable->capacity);
            if(!isPTFull)
            {
                // We are free to insert as long as the page table is not full
                insertPage(pgTable, page);
                enqueue(circularQ, page);
            }
            else
            {
                // If the page table is full, we need to check if the page is already in memory
                int memPosition = MemoryPosition(pgTable, page);
                if (memPosition != -1)
                    // If it is, we need to increment the reference bit
                    pgTable->entries[memPosition].referenceBit = 1;
                else
                {
                    // otherwise, we need to replace the first page in memory whose reference bit is 0
                    
                }
            }

            // Verificar se a página já está na memória e incrementar o bit de referência
            
        }
        
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
            int pageToBeRenewed = popFromData(stack, page);
            if(pageToBeRenewed == -2)
            {
                // Se não estiver, verificar se a memória está cheia.
                if (isDLStackFull(stack))
                    // Se estiver, remove a página no fundo da pilha.
                    popBottom(stack);   // Essa página se torna suja?

                // Chamar método para adicionar a página.
                push(stack, page);
            }
            else if(pageToBeRenewed == -1)
                continue;  // Se estiver na memoria e no topo da pilha não faz nada
            else
                // Se não estiver(no topo), empilhar no topo, ja que a pagina foi removida previamente.
                push(stack, pageToBeRenewed);             
        }
        destroyDLStack(stack);
        fclose(file);
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