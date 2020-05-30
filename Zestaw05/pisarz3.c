#include "a6.h"
#include "shmem.h"
#include "sem.h"
int main(int argc, char const *argv[])
{
    semid semPisQ = semOpen(SEM_PISQ); //semafor (kolejka)
    semid semRsc = semOpen(SEM_RSC);    //semafor operujęcy zasobem
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int)); //zasoby
    pid_t pid = getpid();
    srand(pid);
    while((*r) < 30){
        semP(semPisQ);
        semP(semRsc);
        semV(semPisQ);
        printf("pisarz (%d) : %d\n", pid, *r);
        (*r)++;
        semV(semRsc);
        usleep(rand() % 100);
    }
    semClose(semPisQ);
    semClose(semRsc);
    shmClose(r, rsc, sizeof(int));
    return 0;
}
