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
        setpgid(0, 0);
        
        signal(atoi(argv[2]), SIG_IGN);
        pid_t frk1, waitArg1, wait_pid;
        for (int i = 0; i < 3; i++)
        {

            switch (frk1 = fork())
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

                break;
            };
        }
        for (int i = 0; i < 3; i++)
        {
            if ((wait_pid = wait(&waitArg1)) == -1) //procesy macierzyste czekają na potomne
            {
                perror("wait error");
            }
            else
            {
                printf("child PID: %d status: %d\n", wait_pid, waitArg1);
            }
        }
        exit(0);
        break;
    default:
        sleep(1);
        if (kill(-1 * frk, 0) == -1)
        {
            perror("brak grupy procesow");
            exit(1);
        }
        else
        {
            if (kill(-1 * frk, atoi(argv[2])) == -1)
            {
                perror("kill error");
                exit(1);
            }
        }
        if ((wait(&waitArg)) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
        break;
    };

    return 0;
}
