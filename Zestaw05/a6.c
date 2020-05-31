#include "a6.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sem.h"
#include "shmem.h"
int main(int argc, char const *argv[])
{
    const char *czytelnik[] = {"./czytelnik1.x", "./czytelnik2.x", "./czytelnik3.x"};
    const char *pisarz[] = {"./pisarz1.x", "./pisarz2.x", "./pisarz3.x"};
    int choice,liczPis, liczCzyt,lPis;
    switch (argc)
    {
    case 4:
        choice = atoi(argv[1]);
        liczPis=atoi(argv[2]);
        liczCzyt=atoi(argv[3]);
        if (choice < 1 || choice > 3 || liczPis<=0 || liczCzyt<=0)
        {
            printf("Uzycie: ./a6.x n p c\np: liczba pisarzy\nc: liczba czytlnikow\nn:\n1 przywilej czytelnicy\n2 przywilej pisarze\n3 rowne prawa\n");
            return 0;
        }
        break;

    default:
        printf("Uzycie: ./a6.x n p c\np: liczba pisarzy\nc: liczba czytlnikow\nn:\n1 przywilej czytelnicy\n2 przywilej pisarze\n3 rowne prawa\n");
        return 0;
        break;
    }
    pid_t frk;
    
    int *lP;
    //liczPis = 3;
    //liczCzyt = 3;
    semid semCzyt, semRsc,semBlok, semPisQ;
    semCzyt = semCreate(SEM_CZYT, 1);
    semRsc = semCreate(SEM_RSC, 1);
    //if (choice == 2) //tworzenie semaforów przy wariancie 2
    //{
        semBlok = semCreate(SEM_BLOK, 1);  //semafor, który blokuje czytelników
        semPisQ = semCreate(SEM_PISQ, 1); //semafor zatrzymujących innych pisarzy (kolejka)
        lPis = shmCreate(SHM_LPIS, sizeof(int));
        lP=shmMap(lPis, sizeof(int));//licznik pisarzy
        *lP = 0;
    //}
    /*
    if(choice==3)
    {
        semPisQ = semCreate(SEM_PISQ, 1); //semafor (kolejka)
    }*/
    int lCzyt = shmCreate(SHM_LCZ, sizeof(int));
    int *lC = shmMap(lCzyt, sizeof(int));//licznik czytajacych
    *lC = 0;
    int resource = shmCreate(SHM_RSC, sizeof(int));
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
                if (execl(czytelnik[choice - 1], "czytelnik.x", NULL) == -1)
                    perror("execl error");
                exit(1);
            }
            else if (i >= liczCzyt)
            {
                if (execl(pisarz[choice - 1], "pisarz.x", NULL) == -1)
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
    //if (choice == 2) //zamykanie semaforów przy wariancie 2
    //{
        semClose(semBlok);
        semRemove(SEM_BLOK);
        semClose(semPisQ);
        semRemove(SEM_PISQ);
        shmClose(lP,lPis,sizeof(int));
        shmRm(SHM_LPIS);
        
    //}
    /*
    if(choice==3)
    {
        semClose(semPisQ);
        semRemove(SEM_PISQ);
    }*/
    shmClose(lC, lCzyt, sizeof(int));
    shmClose(rsc, resource, sizeof(int));
    shmRm(SHM_LCZ);
    semClose(semCzyt);
    semClose(semRsc);
    semRemove(SEM_CZYT);
    semRemove(SEM_RSC);
    return 0;
}
