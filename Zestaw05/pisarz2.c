#include "a6.h"
#include "shmem.h"
#include "sem.h"
int main(int argc, char const *argv[])
{
    semid semBlok = semOpen(SEM_BLOK);  //semafor, który blokuje czytelników
    semid semPisQ = semOpen(SEM_PISQ); //semafor zatrzymujących innych pisarzy (kolejka)
    semid semRsc = semOpen(SEM_RSC);    //semafor operujęcy zasobem
    int lPis = shmOpen(SHM_LPIS);
    int *lP = shmMap(lPis, sizeof(int)); //licznik pisarzy
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int)); //licznik pisarzy
    pid_t pid = getpid();
    srand(pid);
    while ((*r) < 30)
    {
        semP(semPisQ);
        (*lP)++;
        if ((*lP) == 1){
            semP(semBlok);
            printf("pierwszy pisarz\n");
        }
        semV(semPisQ);
        semP(semRsc);
        (*r)++;
        printf("pisarz (%d) : %d\n", pid, *r);
        semV(semRsc);
        
        semP(semPisQ);
        (*lP)--;
        if ((*lP) == 0){
            semV(semBlok);
            printf("ostatni pisarz\n");
        }
        semV(semPisQ);
        usleep(rand() % 100000);
    }
    semClose(semBlok);
    semClose(semPisQ);
    semClose(semRsc);
    shmClose(lP, lPis, sizeof(int));
    shmClose(r, rsc, sizeof(int));
    return 0;
}
