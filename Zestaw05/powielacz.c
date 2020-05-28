#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"
int main(int argc, char const *argv[])
{
    pid_t frk;
    int i, fc;
    int waitcntr = atoi(argv[2]); //licznik procesów do zaczekania
    
    semCreate("/semPowielacz", 1);
    FILE *f = fopen("numer.txt", "w+");
    fprintf(f,"0");

    fclose(f);
    
    for (i = 0; i < waitcntr; i++)
    {
        switch (frk = fork())
        {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            execl(argv[1], argv[1], NULL);
            break;
        default:

            break;
        };
    }

    for (i = 0; i < waitcntr; i++)
    {
        if (wait(NULL) == -1) //procesy macierzyste czekają na potomne
        {
            perror("wait error");
        }
    }
    
    semRemove("/semPowielacz");

    f = fopen("numer.txt", "r");
    fc = fscanf(f, "%d", &i);
    if (fc != 1)
    {
        printf("fc:%d\n",fc);
    }
    fclose(f);
    printf("koncowy licznik:%d\n", i);
    return 0;
}
