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

#endif