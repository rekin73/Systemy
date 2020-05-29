#define _DEFAULT_SOURCE
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    //semafory
    semid pis = semOpen("/pisarz");
    semid cz = semOpen("/czytelnik");
    //pamięci dzielone
    int lCz = shmOpen("/czytelnicy");
    int *lC = shmMap(lCz, sizeof(int)); //pamięć mapowana na int (liczba obecnie czytających)
    int rsc = shmOpen("/resource");
    int *r = shmMap(rsc, sizeof(int)); //pamięć mapowana na int (dane do odczytu)
    pid_t pid = getpid();
    srand(pid);
    while ((*r) != 100)
    {
        semP(cz);
        (*lC)++;
        if ((*lC) == 1)
        {
            semP(pis);
        }
        semV(cz);
        /*Wykonywanie czytania*/
        printf("czytelnik (%d) : %d\n", pid, *r);

        semP(cz);
        (*lC)--;
        if ((*lC) == 0)
        {
            semV(pis);
        }
        semV(cz);
        usleep(rand() % 100000); //symulowanie braku potrzeby odczytu przez pewien czas
    }
    /*Zamykanie zasobów*/
    shmClose(r, rsc, sizeof(int));
    shmClose(lC, lCz, sizeof(int));
    semClose(pis);
    semClose(cz);

    return 0;
}
