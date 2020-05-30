#include "a6.h"
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    //semafory
    semid semRsc = semOpen(SEM_RSC);
    semid cz = semOpen(SEM_CZYT);
    //pamięci dzielone
    int lCz = shmOpen(SHM_LCZ);
    int *lC = shmMap(lCz, sizeof(int)); //pamięć mapowana na int (liczba obecnie czytających)
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int)); //pamięć mapowana na int (dane do odczytu)
    pid_t pid = getpid();
    srand(pid);
    while ((*r) != 30)
    {
        semP(cz);
        (*lC)++;
        if ((*lC) == 1)
        {
            semP(semRsc);
        }
        semV(cz);
        /*Wykonywanie czytania*/
        printf("czytelnik (%d) : %d\n", pid, *r);

        semP(cz);
        (*lC)--;
        if ((*lC) == 0)
        {
            semV(semRsc);
        }
        semV(cz);
        usleep(rand() % 100000); //symulowanie braku potrzeby odczytu przez pewien czas
    }
    /*Zamykanie zasobów*/
    shmClose(r, rsc, sizeof(int));
    shmClose(lC, lCz, sizeof(int));
    semClose(semRsc);
    semClose(cz);

    return 0;
}
