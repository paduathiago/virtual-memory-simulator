#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    unsigned addr, page;
    char mode;

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

    if (strcmp(algorithm, "2a"))
    {
        while (fscanf(file, "%u %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            
            CircularQueue * circularQ = createCircularQueue(pgTable->capacity);
            if(!isPTFull(pgTable))
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
                    // the key factor here is using the clock pointer in a way that we can find the right victim and keep a short error rate
                    int pageToBeReplaced = itemReplacement(circularQ, page);
                    PageTableEntry * replaced = replacePage(pgTable, pageToBeReplaced, page);
                }
            }
        }
        fclose(file);
    }
    else if (strcmp(algorithm, "fifo"))
    {
        // The queue size is equivalent to the memory size divided by the page size. This represents the number of pages in memory
        queue_t * queue = createQueue(pgTable->capacity);  
        while (fscanf(file, "%u %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            if(!isInQueue(queue, page))
            {
                // If the page is not in memory, we need to check if the memory is full 
                if (isQueueFull(queue))
                {
                    // If it is, we need to replace the oldest page in memory
                    node_t * pageToBeReplaced = popFront(queue);
                    PageTableEntry * replaced = replacePage(pgTable, pageToBeReplaced->value, page);
                    pushBack(queue, page);
                    // Essa página se torna suja?
                }
                else
                {
                    insertPage(pgTable, page);
                    pushBack(queue, page);
                }
            }
            // If the page is already in memory, we do nothing  
        }
        destroyQueue(queue);
        fclose(file);
    }
    else if (strcmp(algorithm, "lru"))
    {
        struct DoublyLinkedStack * stack = createDLStack(pgTable->capacity);  
        while (fscanf(file, "%u %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            // Verificar se a página já está na memória
            int pageToBeRenewed = popFromData(stack, page);
            if(pageToBeRenewed == -2)
            {
                // Se não estiver, verificar se a memória está cheia.
                if (isDLStackFull(stack))
                {
                    // Se estiver, remove a página no fundo da pilha.
                    int pageToBeReplaced = popBottom(stack);
                    PageTableEntry * replaced = replacePage(pgTable, pageToBeReplaced, page);
                    // Essa página se torna suja?
                    push(stack, page);
                }
                else
                {
                    push(stack, page);
                    insertPage(pgTable, page);
                }    
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
    else if (strcmp(algorithm, "random"))
    {
        while (fscanf(file, "%u %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            if(!isPTFull(pgTable))
                insertPage(pgTable, page);
            else
                replaceRandom(pgTable, page);
        }
    }
    else
    {
        printf("Error: Invalid algorithm\n");
        return 1;
    }

    printf("Input file: %s\n", fileName);
    printf("Memory Size: %d\n", memorySize);
    printf("Page Size: %d\n", pageSize);
    printf("Replacement Algorithm: %s\n", algorithm);
    //printf("Page Faults: %d\n", pgTable->pageFaults);
    //printf("Page Hits: %d\n", pgTable->pageHits);

    return 0;
}