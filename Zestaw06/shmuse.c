#include "shmem.h"
int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        printf("./shmuse.x c size - Tworzy segment pamięci dzielonej o rozmiarze size bajtów.\n");
        printf("./shmuse.x d - Usuwa segment pamięci dzielonej\n");
        printf("./shmuse.x r - Wypisuje zawartość pamięci dzielonej na standardowe wyjście.\n");
        printf("./shmuse.x w < input.txt - Kopiuje zawartość standardowego wejścia do pamięci dzielonej.\n");
        printf("./shmuse.x i - Wypisuje informacje o pamięci dzielonej.\n");
        printf("./shmuse.x - Wypisuje informacje o użyciu tego programu.\n");
        return 0;
    }
    else if (argv[1][1] != '\0')
    {
        printf("zle argumenty\n");
        return 0;
    }
    else if (argc > 2 && argv[1][0] != 'c')
    {
        printf("zle argumenty\n");
        return 0;
    }

    int size, rd;
    int shm;
    char *buf = malloc(100);
    void *ptr;
    switch (argv[1][0])
    {
    case 'c':

        if ((size = atoi(argv[2])) == 0 && argv[2][0] != '0')
        {
            printf("zle argumenty: argument size jest liczba\n");
            return 0;
        }
        shmCreate("/shmUse", size);
        break;

    case 'd':
        shmRm("/shmUse");
        break;

    case 'r':
        shm = shmOpen("/shmUse");
        size = shmSize(shm);
        
        ptr = shmMap(shm, size);
        while ((rd = read(shm, buf, 100)) != 0)
        {
            
            if (write(1, buf, rd) == -1)
            {
                perror("write error");
                exit(1);
            }
        }
        
        shmClose(ptr, shm, size);
        break;

    case 'w':
        shm = shmOpen("/shmUse");
        size = shmSize(shm);
        ptr = shmMap(shm, size);
        printf("size:%d",size);
        while ((rd = read(0, buf, 100)) != 0)
        {
            
            if (write(shm, buf, rd) == -1)
            {
                perror("write error");
                exit(1);
            }
        }
        printf("size:%d",shmSize(shm));
        shmClose(ptr, shm, size);
        break;

    case 'i':
        shm = shmOpen("/shmUse");
        size = shmSize(shm);
        ptr = shmMap(shm, size);
        shmInfo(shm);
        shmClose(ptr, shm, size);
        break;

    default:
        printf("zle argumenty\n");
        return 0;
        break;
    };
free(buf);
    /* code */
    return 0;
}
