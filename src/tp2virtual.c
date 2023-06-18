#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circular_queue.h"
#include "doubly_linked_stack.h"
#include "page_table.h"
#include "queue.h"

int sValue(int pageSize)
{
    int tmp = pageSize * 1024;
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
    
    unsigned dirtyPages = 0, pageFaults = 0;
    char mode;
    unsigned addr, page;

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

    if (strcmp(algorithm, "2a") == 0)
    {   
        CircularQueue * circularQ = createCircularQueue(pgTable->capacity);
        while (fscanf(file, "%x %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
        
            int memPosition = MemoryPosition(pgTable, page);
            //printf("memPosition: %d\n", memPosition);

            // This means the page is already in memory
            if(memPosition != -1)
                pgTable->entries[memPosition].referenceBit = 1;

            else
            {
                pageFaults++;
                if(!isPTFull(pgTable))
                {
                    // We are free to insert as long as the page table is not full and the page is not already in memory
                    insertPage(pgTable, page, mode);
                    enqueue(circularQ, page, mode);
                    //printf("page table size: %d %d\n", pgTable->entries[pgTable->size-1].pageNumber, pgTable->size);
                }
                else
                {
                    // We need to replace the first page in memory whose reference bit is 0
                    // the key factor here is using the clock pointer in a way that we can find the right victim and keep a short error rate
                    int pageToBeReplaced = itemReplacement(circularQ, page, mode);
                    //printf("page to be replaced: %d\n", pageToBeReplaced);
                    PageTableEntry replaced = replacePage(pgTable, pageToBeReplaced, page, mode);
                    
                    if (replaced.dirtyBit == 1)
                        dirtyPages++;
                }
            }
        }
    }
    else if (strcmp(algorithm, "fifo") == 0)
    {
        queue_t * queue = createQueue(pgTable->capacity);
        //printf("page table capacity: %d\n", pgTable->capacity);  
        while (fscanf(file, "%x %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            if(!isInQueue(queue, page))
            {
                pageFaults++;
                // If the page is not in memory, we need to check if the memory is full 
                if (isQueueFull(queue))
                {
                    // If it is, we need to replace the oldest page in memory
                    node_t * pageToBeReplaced = popFront(queue);
                    PageTableEntry replaced = replacePage(pgTable, pageToBeReplaced->value, page, mode);
                    pushBack(queue, page);
                    
                    if (replaced.dirtyBit == 1)
                        dirtyPages++;
                }
                else
                {
                    insertPage(pgTable, page, mode);
                    pushBack(queue, page);
                }
            }
            // If the page is already in memory, we do nothing  
        }
        destroyQueue(queue);
    }
    else if (strcmp(algorithm, "lru") == 0)
    {
        struct DoublyLinkedStack * stack = createDLStack(pgTable->capacity);  
        while (fscanf(file, "%x %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            
            if(!isDLStackFull(stack))
            {
                pageFaults++;
                push(stack, page);
                insertPage(pgTable, page, mode);
            }

            else  
            {
                int pageToBeRenewed = popFromData(stack, page);
                
                if(pageToBeRenewed == -1)  // Page is in memory and on top of the stack
                    continue;
                else if(pageToBeRenewed == -2)  // Page is not in memory
                {
                    pageFaults++;
                    //We pop the bottom of the stack and replace it with the new page
                    int pageToBeReplaced = popBottom(stack);
                    PageTableEntry replaced = replacePage(pgTable, pageToBeReplaced, page, mode);
                    push(stack, page);

                    if (replaced.dirtyBit == 1)
                        dirtyPages++;
                }
                // Page is in memory but not on top of the stack
                else
                    // Since page has been previously removed, Push page(put on top)
                    push(stack, pageToBeRenewed);
            }            
        }
        destroyDLStack(stack);
    }
    else if (strcmp(algorithm, "random") == 0)
    {
        while (fscanf(file, "%x %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            int memPosition = MemoryPosition(pgTable, page);
            //printf("memPosition: %d\n", memPosition);
            if(memPosition == -1)
            {
                pageFaults++;
                if(!isPTFull(pgTable))
                {
                    insertPage(pgTable, page, mode);
                }
                else
                {
                    PageTableEntry replaced = replaceRandom(pgTable, page, mode);
                    if (replaced.dirtyBit == 1)
                        dirtyPages++;
                }
            }    
        }
    }
    else
    {
        printf("Error: Invalid algorithm\n");
        return 1;
    }
    fclose(file);

    printf("Input file: %s\n", fileName);
    printf("Memory Size: %d\n", memorySize);
    printf("Page Size: %d\n", pageSize);
    printf("Replacement Algorithm: %s\n", algorithm);
    printf("Written pages: %d\n", dirtyPages);
    printf("Page Faults: %d\n", pageFaults);

    return 0;
}