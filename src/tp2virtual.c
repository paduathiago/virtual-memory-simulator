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
        int clockPointer = 0;
        while (fscanf(file, "%x %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
        
            int memPosition = MemoryPosition(pgTable, page);

            // This means the page is already in memory
            if(memPosition != -1)
            {
                pgTable->entries[memPosition].referenceBit = 1;
                if(mode == 'W')
                    pgTable->entries[memPosition].dirtyBit = 1;
            }
 
            else
            {
                pageFaults++;
                if(isPTFull(pgTable))
                {
                    PageTableEntry * newPage = createPageTableEntry(page, mode);
                    while (pgTable->entries[clockPointer].referenceBit == 1)
                    {
                        pgTable->entries[clockPointer].referenceBit = 0;
                        clockPointer = (clockPointer + 1) % pgTable->capacity;
                    }
                    
                    if(pgTable->entries[clockPointer].dirtyBit == 1)
                        dirtyPages++;
                    
                    pgTable->entries[clockPointer] = *newPage;
                    clockPointer = (clockPointer + 1) % pgTable->capacity;
                }
                else
                    insertPage(pgTable, page, mode);
            }
        }
    }
    else if (strcmp(algorithm, "fifo") == 0)
    {
        queue_t * queue = createQueue(pgTable->capacity);
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
            else
            {
                if(mode == 'W')
                    pgTable->entries[MemoryPosition(pgTable, page)].dirtyBit = 1;
            }
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
                if(isInDLStack(stack, page))
                {
                    if(mode == 'W')
                        pgTable->entries[MemoryPosition(pgTable, page)].dirtyBit = 1;
                }
                else
                {
                    pageFaults++;
                    push(stack, page);
                    insertPage(pgTable, page, mode);
                }
            }

            else  
            {
                int pageToBeRenewed = popFromData(stack, page);
                
                if(pageToBeRenewed == -1)  // Page is in memory and on top of the stack
                {
                    if(mode == 'W')
                        pgTable->entries[MemoryPosition(pgTable, page)].dirtyBit = 1;
                }
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
                {
                    if(mode == 'W')
                        pgTable->entries[MemoryPosition(pgTable, page)].dirtyBit = 1;
                    // Since page has been previously removed, Push page(put on top)
                    push(stack, pageToBeRenewed);
                }            
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
            else
            {
                if(mode == 'W')
                    pgTable->entries[memPosition].dirtyBit = 1;
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