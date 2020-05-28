/* Implementacja rozwiązania czytelnik wchodzi do czytelni jak najszybciej*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sem.h"
int main(int argc, char const *argv[])
{
    pid_t frk;
    int liczPis, liczCzyt;
    liczPis=1;
    liczCzyt=3;
    semid semCzyt,semPis;
    semCzyt=semCreate("/czytelnik",1);
    semPis=semCreate("/pisarz",1);
    for (int i = 0; i < liczPis+liczCzyt; i++)
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
                if (execl("./czytelnik.x", "czytelnik.x", NULL) == -1)
                    perror("execl error");
                exit(1);
            }
            else if (i >= liczCzyt)
            {
                if (execl("./pisarz.x", "pisarz.x", NULL) == -1)
                    perror("execl error");
                exit(1);
            }

            break;
        default:
            break;
        }
    }
for(int i = 0; i < liczPis+liczCzyt; i++){
    if(wait(NULL)==-1){
        perror("wait error");
        exit(1);
    }
}
semClose(semCzyt);
semClose(semPis);
semRemove("/czytelnik");
semRemove("/pisarz");
    return 0;
}
