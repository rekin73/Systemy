#define _DEFAULT_SOURCE
#include "shmem.h"
#include "sem.h"
#include "bufor.h"
int main(int argc, char const *argv[])
{
    semid prod, kons, prodQ;
    int f, rd, buf;
    prod = semOpen("/producent");
    prodQ = semOpen("/prodQ");
    //konsQ = semOpen("/konsQ");
    kons = semOpen("/konsument");
    buf = shmOpen("/bufor");
    bufor *bf = (bufor *)shmMap(buf, sizeof(bufor));
    towar tmp;
    pid_t pid = getpid();
    srand(pid);
    if ((f = open("magazyn.txt", O_RDONLY | O_APPEND)) == -1)
    {
        perror("open error");
        exit(1);
    }
rd=1;
    //semP(prod);
    while (rd > 0 && bf->size!=-1)
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
            semP(prodQ);
            rd = pread(f, &tmp, sizeof(towar),bf->offset);
            if(rd>0 && bf->size!=-1){
                bf->buf[bf->end]=tmp;
                bf->offset++;
            //bf->buf[bf->end] = tmp;
            //bf->size++;
            //usleep(rand() % 10000);
            //usleep(500000);
            //sleep(1);
            printf("producent(%d): buf[%d]=%c\n",pid,bf->end, bf->buf[bf->end]);
            (bf->end)++;
            if (bf->end == ROZMIAR)
            {
                bf->end = 0;
            }
            
/*             for (int i = 0; i < ROZMIAR; i++)
            {
                if(i==bf->end)
                    printf("\033[31m%c \033[0m",bf->buf[i]);
                else if(i==bf->beg)
                    printf("\033[32m%c \033[0m",bf->buf[i]);
                else if (bf->beg==bf->end && bf->end ==i)
                    printf("\033[33m%c \033[0m",bf->buf[i]);
                else
                    printf("\033[0m%c \033[0m",bf->buf[i]);

            }
            printf("\n"); */
            }
            semV(prodQ);
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
    semClose(prodQ);
    semClose(kons);
    shmClose(bf, buf, sizeof(bufor));

    return 0;
}