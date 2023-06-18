#include "page_table.h"

PageTableEntry* createPageTableEntry(int pageNumber, char mode) 
{
    PageTableEntry* entry = malloc(sizeof(PageTableEntry));
    entry->pageNumber = pageNumber;
    entry->referenceBit = 0;
    entry->dirtyBit = (mode == 'W') ? 1 : 0;
    return entry;
}

PageTable* createPageTable(int capacity) 
{
    PageTable* table = malloc(sizeof(PageTable));
    table->entries = malloc(capacity * sizeof(PageTableEntry));
    table->size = 0;
    table->capacity = capacity;

    for (int i = 0; i < capacity; i++)
    {
        table->entries[i].pageNumber = -1;
        table->entries[i].referenceBit = 0;
        table->entries[i].dirtyBit = 0;
    }

    return table;
}

int isPTFull(PageTable* table){
    return table->size == table->capacity;
}

int MemoryPosition(PageTable* table, int pageNumber)
{
    for(int i = 0; i < table->size; i++){
        if(table->entries[i].pageNumber == pageNumber)
            return i;
    }
    return -1;  // page not found
}

void insertPage(PageTable* table, int pageNumber, char mode) 
{
    PageTableEntry * entry = createPageTableEntry(pageNumber, mode);
    table->entries[table->size] = *entry;
    table->size++;
}

PageTableEntry replacePage(PageTable* table, int removedPage, int newPage, char mode) 
{
    int memPosition = MemoryPosition(table, removedPage);
    PageTableEntry replaced;
    PageTableEntry *newEntry = createPageTableEntry(newPage, mode);

    if (memPosition != -1)
    {
        replaced = table->entries[memPosition];
        table->entries[memPosition] = *newEntry;
        return replaced;
    }
    else
    {
        printf("Error! Page not found in memory\n");
        return;
    }
}

PageTableEntry replaceRandom(PageTable* table, int pageNumber, char mode) 
{
    PageTableEntry replaced;
    PageTableEntry *newEntry = createPageTableEntry(pageNumber, mode);
    
    int random = rand() % table->size;
    //printf("Random number: %d\n", random);
    replaced = table->entries[random];
    table->entries[random] = *newEntry;

    return replaced;
}