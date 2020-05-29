/* Implementacja rozwiązania czytelnik wchodzi do czytelni jak najszybciej*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    const char *czytelnik[] = {"./czytelnik1.x", "./czytelnik2.x", "./czytelnik3.x"};
    const char *pisarz[] = {"./pisarz1.x", "./pisarz2.x", "./pisarz3.x"};
    int choice;
    switch (argc)
    {
    case 2:
        choice = atoi(argv[1]);
        if (choice < 1 || choice > 3)
        {
            printf("Uzycie: ./a6.x n\nn:\n1 przywilej czytelnicy\n2 przywilej pisarze\n3 rowne prawa\n");
            return 0;
        }
        break;

    default:
        printf("Uzycie: ./a6.x n\nn:\n1 przywilej czytelnicy\n2 przywilej pisarze\n3 rowne prawa\n");
        return 0;
        break;
    }
    pid_t frk;
    int liczPis, liczCzyt;
    liczPis = 1;
    liczCzyt = 3;
    semid semCzyt, semPis;
    semCzyt = semCreate("/czytelnik", 1);
    semPis = semCreate("/pisarz", 1);
    int lCzyt = shmCreate("/czytelnicy", sizeof(int));
    int *lC = shmMap(lCzyt, sizeof(int));

    *lC = 0;
    int resource = shmCreate("/resource", sizeof(int));
    int *rsc = shmMap(resource, sizeof(int));

    *rsc = 0;
    for (int i = 0; i < liczPis + liczCzyt; i++)
    {
        switch (frk = fork())
        {
        case -1:
            perror("fork error");
            exit(1);
            break;
        case 0:
            if (i < liczCzyt)
            {
                if (execl(czytelnik[choice-1], "czytelnik.x", NULL) == -1)
                    perror("execl error");
                exit(1);
            }
            else if (i >= liczCzyt)
            {
                if (execl(pisarz[choice-1], "pisarz.x", NULL) == -1)
                    perror("execl error");
                exit(1);
            }

            break;
        default:
            break;
        }
    }
    for (int i = 0; i < liczPis + liczCzyt; i++)
    {
        if (wait(NULL) == -1)
        {
            perror("wait error");
            exit(1);
        }
    }
    shmClose(lC, lCzyt, sizeof(int));
    shmClose(rsc, resource, sizeof(int));
    shmRm("/czytelnicy");
    semClose(semCzyt);
    semClose(semPis);
    semRemove("/czytelnik");
    semRemove("/pisarz");
    return 0;
}
