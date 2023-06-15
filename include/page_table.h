#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pageNumber;
    int referenceBit;
} PageTableEntry;

PageTableEntry* createPageTableEntry(int pageNumber);

typedef struct {
    PageTableEntry* entries;
    int size;
    int capacity;
} PageTable;

PageTable* createPageTable(int capacity);
void insertPage(PageTable* table, int pageNumber);
PageTableEntry* replacePage(PageTable* table, int removedPage, int newPage);
PageTableEntry* replaceRandom(PageTable* table, int pageNumber);
int isPTFull(PageTable* table);
int MemoryPosition(PageTable* table, int pageNumber);

#endif