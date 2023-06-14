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

int main(int argc, char *argv[])
{
    char * algorithm = argv[1];
    char * fileName = argv[2];
    int page_size = atoi(argv[3]);
    int memorySize = atoi(argv[4]);

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
        
        char address[9];
        char mode;

        while (fscanf(file, "%8s %c", address, &mode) == 2) 
        {
            
        }
        
        struct Queue * queue = createQueue(memorySize);
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