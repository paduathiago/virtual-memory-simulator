#include <stdio.h>

#include "queue.h"

FILE * openFile(char *file) {
    FILE *file = fopen(file, "r");
    if (file == NULL) 
    {
        printf("Invalid File!.\n");
        return 1;
    }
    return file;
}

int sValue(int pageSize)
{
    int tmp = pageSize;
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

    unsigned s = sValue(pageSize);

    if (argc != 5)
    {
        printf("Error: Invalid arguments\n");
        return 1;
    }

    if (algorithm == '2a')
    {

    }
    else if (algorithm == 'fifo')
    {
        FILE * file = openFile(fileName);
        unsigned addr, page;
        char mode;

        // The queue size is the memory size divided by the page size. This represents the number of pages in memory
        struct Queue * queue = createQueue(memorySize/pageSize);  
        while (fscanf(file, "%8s %c", &addr, &mode) == 2) 
        {
            page = addr >> s;
            // Chamar método para enfileirar a página.
            // Verificar se a página já está na memória.
            // Se não estiver, verificar se a memória está cheia.
            // Se estiver, desenfileirar a página mais antiga.
            // Enfileirar a página atual.
        }
        fclose(file);
    }
    else if (algorithm == 'lru')
    {

    }
    else if (algorithm == 'random')
    {

    }
    else
    {
        printf("Error: Invalid algorithm\n");
        return 1;
    }

    return 0;
}