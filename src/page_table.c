#include "page_table.h"

PageTable* createPageTable(int capacity) {
    PageTable* table = malloc(sizeof(PageTable));
    table->entries = malloc(capacity * sizeof(PageTableEntry));
    table->size = 0;
    table->capacity = capacity;
    return table;
}