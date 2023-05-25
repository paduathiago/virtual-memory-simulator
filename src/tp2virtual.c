int main(int argc, char *argv[])
{
    char * algorithm = argv[1];
    char * file = argv[2];
    int page_size = atoi(argv[3]);
    int memory_size = atoi(argv[4]);

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