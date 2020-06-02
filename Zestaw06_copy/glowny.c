#include "sem.h"
#include "shmem.h"
#include <sys/wait.h>
#include "bufor.h"

int main(int argc, char const *argv[])
{
    semCreate("/producent", ROZMIAR);
    semCreate("/konsument", 0);
    semCreate("/prodQ", 1);
    semCreate("/konsQ", 1);
    int buf = shmCreate("/bufor", sizeof(bufor));
    bufor *bf = shmMap(buf, sizeof(bufor));
    (*bf) = (bufor){1, 0, 0,""};
    for(int i=0;i<3;i++){
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:

        if (execl("./konsument.x", "./konsument.x", NULL) == -1)
        {
            perror("execl error");
            exit(1);
        }

        break;
    default:

        break;
    };
    }
    for(int i=0;i<3;i++){
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:

        if (execl("./producent.x", "./producent.x", NULL) == -1)
        {
            perror("execl error");
            exit(1);
        }

        break;
    default:

        break;
    };
    }
   
    for (int i = 0; i < 6; i++)
    {
        printf("fun,%d\n",i);
        if ((wait(NULL)) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
    }
    shmRm("/bufor");
    semRemove("/producent");
    semRemove("/konsument");
    semRemove("/prodQ");
    semRemove("/konsQ");
    return 0;
}
