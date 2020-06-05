#include "sem.h"
#include "shmem.h"
#include <sys/wait.h>
#include "bufor.h"
#define LPROD 2
#define LKONS 2

int main(int argc, char const *argv[])
{
    semCreate("/producent", ROZMIAR);
    semCreate("/konsument", 0);
    semCreate("/prodQ", 1);
    semCreate("/konsQ", 1);
    int file = shmCreate("/file",sizeof(int));//pamięć dzielona dla deskryptora pliku
    int f;//deskryptor pliku schowek.txt
        if ((f = open("schowek.txt", O_CREAT | O_TRUNC | O_APPEND, 0666)) == -1)//czyszczenie zawartości pliku
    {
        perror("open error");
        exit(1);
    }
    close(f);
/*     if ((f = open("magazyn.txt", O_RDONLY)) == -1)
    {
        perror("open error");
        exit(1);
    } */
    shmMap(file,sizeof(int));//odwzorowanie w pamięci dla deskryptora pliku mag
    int buf = shmCreate("/bufor", sizeof(bufor));
    bufor *bf = shmMap(buf, sizeof(bufor));
    (*bf) = (bufor){1, 0, 0, ""};
    for (int i = 0; i < LKONS; i++)
    {
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
    for (int i = 0; i < LPROD; i++)
    {
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

    for (int i = 0; i < LPROD + LKONS; i++)
    {
        printf("fun,%d\n", i);

        if ((wait(NULL)) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
    }
    for (int j = 0; j < ROZMIAR; j++)
    {
        if (j == bf->end)
            printf("\033[31m%c \033[0m", bf->buf[j]);
        else if (j == bf->beg)
            printf("\033[32m%c \033[0m", bf->buf[j]);
        else if (bf->beg == bf->end && bf->end == j)
            printf("\033[33m%c \033[0m", bf->buf[j]);
        else
            printf("\033[0m%c \033[0m", bf->buf[j]);
    }
    //zamykanie i usuwanie odwzorowania magazynu
    //close(f);
    shmRm("/file");

    shmRm("/bufor");
    semRemove("/producent");
    semRemove("/konsument");
    semRemove("/prodQ");
    semRemove("/konsQ");
    return 0;
}
