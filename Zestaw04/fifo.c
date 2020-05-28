#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    char *fifo = "potok";
    
    if (mkfifo(fifo, 0666) == -1) //procesy macierzyste czekają na potomne
    {
        perror("mkfifo error");
    }
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:

        if (execl("./konsument.x", "./konsument.x", fifo, NULL) == -1)
        {
            perror("execl error");
            exit(1);
        }

        break;
        default:
            sleep(1);
        break;
    };
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:
        
        if (execl("./producent.x", "./producent.x", fifo, NULL) == -1)
        {
            perror("execl error");
            exit(1);
        }
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
    if (unlink(fifo) == -1) //procesy macierzyste czekają na potomne
    {
        perror("unlink error");
    }
    return 0;
}
