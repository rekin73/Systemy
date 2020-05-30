#include "a6.h"
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    semid semRsc = semOpen(SEM_RSC);
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int));
    pid_t pid = getpid();
    srand(pid);
    while ((*r) < 30)
    {
        semP(semRsc);
        (*r)++;
        printf("pisarz (%d) : %d\n", pid, *r);
        semV(semRsc);
        usleep(rand() % 100000);
    }
    shmClose(r, rsc, sizeof(int));
    semClose(semRsc);
    return 0;
}
