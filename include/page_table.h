#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>

typedef struct {
    PageTableEntry* entries;
    int size;
    int capacity;
} PageTable;

PageTable* createPageTable(int capacity);
void insertPageTableEntry(PageTable* table, int address);
int isPTFull(PageTable* table);
int MemoryPosition(PageTable* table, int pageNumber);

typedef struct {
    int pageNumber;
    int referenceBit;
} PageTableEntry;

#endif