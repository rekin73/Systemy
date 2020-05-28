#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t frk, waitArg;
    switch (frk = fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:

        if (execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL) == -1)
        {
            perror("execl error");
            exit(1);
        }
        break;
    default:
        sleep(1);
        if (kill(frk, 0) == -1)
        {
            perror("brak procesu");
            exit(1);
        }
        else
        {
            if (kill(frk, atoi(argv[2])) == -1)
            {
                perror("kill error");
                exit(1);
            }
        }
        break;
    };

    if ((wait(&waitArg)) == -1) //procesy macierzyste czekają na potomne
    {
        perror("wait error");
    }
    return 0;
}
