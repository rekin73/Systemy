#include "a6.h"
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    
    semid semCzyt = semOpen(SEM_CZYT);
    semid semBlok = semOpen(SEM_BLOK); //semafor, który blokuje czytelników
    semid semRsc = semOpen(SEM_RSC);
    int lCzyt = shmOpen(SHM_LCZ);
    int *lC = shmMap(lCzyt, sizeof(int)); //licznik czytajacych
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int)); //pamięć mapowana na int (dane do odczytu)
    pid_t pid = getpid();
    srand(pid);
    while ((*r) < 30)
    {
        semP(semBlok);
        semP(semCzyt);
        (*lC)++;
        if ((*lC) == 1)
        {
            semP(semRsc);
        }
        semV(semCzyt);
        semV(semBlok);
        printf("Czytelnik (%d): %d\n", pid, *r);
        semP(semCzyt);
        (*lC)--;
        if ((*lC) == 0)
        {
            semV(semRsc);
        }
        semV(semCzyt);
        usleep(rand() % 100000);
    }

    semClose(semCzyt);
    semClose(semBlok);
    semClose(semRsc);
    shmClose(lC, lCzyt, sizeof(int));
    shmClose(r, rsc, sizeof(int));
    return 0;
}
