#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pageNumber;
    int referenceBit;
    int dirtyBit;
} PageTableEntry;

PageTableEntry* createPageTableEntry(int pageNumber, char mode);

typedef struct {
    PageTableEntry* entries;
    int size;
    int capacity;
} PageTable;

PageTable* createPageTable(int capacity);
void insertPage(PageTable* table, int pageNumber, char mode);
PageTableEntry replacePage(PageTable* table, int removedPage, int newPage, char mode);
PageTableEntry replaceRandom(PageTable* table, int pageNumber, char mode);
int isPTFull(PageTable* table);
int MemoryPosition(PageTable* table, int pageNumber);

#endif