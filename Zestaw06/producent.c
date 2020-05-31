#define _DEFAULT_SOURCE
#include "shmem.h"
#include "sem.h"
#include "bufor.h"
int main(int argc, char const *argv[])
{
    semid prod, kons;
    int f, rd, buf;
    prod = semOpen("/producent");
    kons = semOpen("/konsument");
    buf = shmOpen("/bufor");
    bufor *bf = (bufor *)shmMap(buf, sizeof(bufor));
    towar tmp;
    if ((f = open("magazyn.txt", O_RDONLY)) == -1)
    {
        perror("open error");
        exit(1);
    }

    //semP(prod);
    while ((rd = read(f, &tmp, sizeof(towar))) > 0)
    {
        /*         if (bf->size == ROZMIAR) //pełny
        {
            if (bf->beg == bf->end)
            {
                semV(kons);
                semInfo(kons);
                printf("pelny");
            }
        } */
        //printf("prod:beg -> %d end -> %d\n",bf->beg,bf->end);
        semInfo(prod);
        semP(prod);

        bf->buf[bf->end] = tmp;
        //bf->size++;
        usleep(rand()%10000);
        printf("producent: %c\n", tmp);
        if ((bf->end)++ == ROZMIAR)
        {
            bf->end = 0;
        }
        semV(kons);
        /*         if (bf->size == 1) //był pusty
        {
            //if (bf->beg == bf->end)
            semV(kons);
            semInfo(kons);
        } */
    }
    if (rd == -1)
    {
        perror("read error");
        exit(1);
    }
    
    if (rd == 0)
    {
        //semV(kons);
        bf->size = -1;
            printf("koniec prod\n");
    }

    close(f);
    semClose(prod);
    semClose(kons);
    shmClose(bf, buf, sizeof(bufor));

    return 0;
}