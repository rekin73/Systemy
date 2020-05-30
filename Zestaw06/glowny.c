#include "sem.h"
#include "shmem.h"
#include <sys/wait.h>
#include "bufor.h"

int main(int argc, char const *argv[])
{
    semCreate("/producent", ROZMIAR);
    semCreate("/konsument", 0);
    int buf=shmCreate("/bufor", sizeof(bufor));
    bufor *bf= shmMap(buf,sizeof(bufor));
    (*bf)=(bufor){1,1,1,"sdf"};
    bf->beg=0;
    bf->end=ROZMIAR-1;
    
    printf("%s\n",(bf->buf));
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

    for (int i = 0; i < 2; i++)
    {
        printf("fun");
        if ((wait(NULL)) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
    }
    shmRm("/bufor");
    semRemove("/producent");
    semRemove("/konsument");
    return 0;
}
