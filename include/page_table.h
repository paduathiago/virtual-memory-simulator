#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>

typedef struct {
    PageTableEntry* entries;
    int size;
    int capacity;
} PageTable;

PageTable* createPageTable(int capacity);

typedef struct {
    int page_number;
    int frame_number;
    int referenceBit;
} PageTableEntry;




#endif