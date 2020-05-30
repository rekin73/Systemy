#include "a6.h"
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    semid semCzyt = semOpen(SEM_CZYT);
    semid semPisQ = semOpen(SEM_PISQ); //semafor (kolejka)
    semid semRsc = semOpen(SEM_RSC);
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int)); //zasoby
        int lCzyt = shmOpen(SHM_LCZ);
    int *lC = shmMap(lCzyt, sizeof(int));//licznik czytajacych
    pid_t pid = getpid();
    srand(pid);
    while ((*r) < 30)
    {
        semP(semPisQ);
        semP(semCzyt);
        (*lC)++;
        if((*lC)==1){
            semP(semRsc);
        }
        semV(semPisQ);
        semV(semCzyt);
        printf("czytelnik (%d) : %d\n",pid,*r);
        semP(semCzyt);
        (*lC)--;
        if((*lC)==0){
            semV(semRsc);
        }
        semV(semCzyt);
    }
    semClose(semPisQ);
    semClose(semRsc);
    semClose(semCzyt);
    shmClose(r, rsc, sizeof(int));
    shmClose(lC,lCzyt,sizeof(int));
    return 0;
}
