#include "a6.h"
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    semid pis = semOpen(SEM_RSC);
    int rsc = shmOpen(SHM_RSC);
    int *r = shmMap(rsc, sizeof(int));
    pid_t pid = getpid();
    srand(pid);
    while ((*r) < 100)
    {
        semP(pis);
        (*r)++;
        printf("pisarz (%d) : %d\n", pid, *r);
        semV(pis);
        usleep(rand() % 100000);
    }
    shmClose(r, rsc, sizeof(int));
    semClose(pis);
    return 0;
}
