#include "sem.h"
#include "shmem.h"
#include "bufor.h"
int main(int argc, char const *argv[])
{
    semid prod, kons;
    int f, rd, buf;
    prod = semOpen("/producent");
    kons = semOpen("/konsument");
    buf =shmOpen("/bufor");
    bufor *bf=(bufor *) shmMap(buf,sizeof(bufor));
        if ((f = open("magazyn.txt", O_RDONLY)) == -1)
    {
        perror("open error");
        exit(1);
    }
    
        //semP(prod);
        printf("%d",bf->beg);

    
    return 0;
}