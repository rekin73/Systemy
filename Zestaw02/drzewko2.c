#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "procinfo.h"
int main(int argc, char const *argv[])
{
    pid_t frk, waitPid;
    int wait_info;
    int i;
    int waitcntr = 0;  //licznik procesów do zaczekania
    int sleepTime = 0; //czas uspienia procesu
    for (i = 0; i < 3; i++)
    {
        switch (frk = fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            /* akcja dla procesu potomnego */
            waitcntr = 0; //zerowanie licznika dla każdego nowego procesu
            sleepTime++;  //zwiekszanie czasu uśpienia co pokolenie

            break;
        default:
            /* akcja dla procesu macierzystego, np. wywolanie funkcji wait */
            waitcntr++; //zwiększanie licznika dla procesu macierzystego
            i = 3;
            break;
        };
    }
    sleep(sleepTime); //uśpienie procesu
    procinfo(argv[0]);   //wyświetlanie informacji o procesie
    for (i = 0; i < waitcntr; i++)
    {
        if ((waitPid = wait(&wait_info)) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
    }
    return 0;
}
