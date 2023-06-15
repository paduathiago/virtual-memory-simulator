#include "page_table.h"

PageTableEntry* createPageTableEntry(int pageNumber) {
    PageTableEntry* entry = malloc(sizeof(PageTableEntry));
    entry->pageNumber = pageNumber;
    entry->referenceBit = 0;
    return entry;
}

PageTable* createPageTable(int capacity) {
    PageTable* table = malloc(sizeof(PageTable));
    table->entries = malloc(capacity * sizeof(PageTableEntry));
    table->size = 0;
    table->capacity = capacity;
    return table;
}

int isPTFull(PageTable* table){
    return table->size == table->capacity;
}

int MemoryPosition(PageTable* table, int pageNumber){
    for(int i = 0; i < table->size; i++){
        if(table->entries[i].pageNumber == pageNumber)
            return i;
    }
    return -1;
}

void insertPage(PageTable* table, int pageNumber) {
    int memPosition = MemoryPosition(table, pageNumber);

    // if page is already in memory, increment reference bit
    if(memPosition != -1)
        table->entries[memPosition].referenceBit = 1;   
    else
    {
        PageTableEntry entry;
        entry.referenceBit = 0;
        table->entries[table->size] = entry;
        table->size++;
    }
}