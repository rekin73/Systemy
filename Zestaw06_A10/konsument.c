#define _DEFAULT_SOURCE
#include "shmem.h"
#include "sem.h"
#include "bufor.h"
int main(int argc, char const *argv[])
{
    semid prod, kons, konsQ;
    int f, wr, buf;
    prod = semOpen("/producent");
    kons = semOpen("/konsument");
    buf = shmOpen("/bufor");
    konsQ = semOpen("/konsQ");
    bufor *bf = (bufor *)shmMap(buf, sizeof(bufor));
    pid_t pid=getpid();
    srand(pid);
    if ((f = open("schowek.txt", O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
    {
        perror("open error");
        exit(1);
    }
    towar tmp;
    wr = 1;
    
    while (wr)
    {
        semP(konsQ);
        if ((bf->beg == bf->end) && (bf->size==-1))
        {
        printf("kons:beg -> %d end -> %d\n", bf->beg, bf->end);
            wr = 0;

        }
        else{
        //semInfo(kons);
        semP(kons);
        tmp = bf->buf[bf->beg];
        wr = write(f, &tmp, sizeof(towar));
        if (wr == -1)
        {
            perror("wrire error");
            exit(1);
        }
        
        usleep(rand()%10000);
        //bf->size--;
        semInfo(kons);
        printf("konsument: %c\n", tmp);
        bf->beg++;
        if (bf->beg == ROZMIAR)
            bf->beg = 0;
        semV(prod);
        }
        semV(konsQ);
    }

    close(f);
    semClose(prod);
    semClose(kons);
    semClose(konsQ);
    shmClose(bf, buf, sizeof(bufor));
    printf("koniec kons\n");
    return 0;
}