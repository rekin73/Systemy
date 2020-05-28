#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "procinfo.h"
#include "procesy.h"
void lider(const char *name)
{
    pid_t frk;
    int wait_info;
    for (int i = 0; i < 3; i++)
    {
        switch (frk = fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            /* akcja dla procesu potomnego */

            setpgid(frk,frk);
            procinfo(name);//wyświetlanie informacji o procesie

            break;
        default:
            /* akcja dla procesu macierzystego, np. wywolanie funkcji wait */
            wait(&wait_info); //procesy macierzyste czekają na potomne

            break;
        };
    }
}