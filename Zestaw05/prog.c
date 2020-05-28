#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include "sem.h"
int main(int argc, char const *argv[])
{
    FILE *f;
    semid sem = semOpen("/semPowielacz");
    int n, fc;
    pid_t pid = getpid();
    for (int i = 0; i < 10; i++)
    {
        printf("\nPID %d: przed ", pid);
        semInfo(sem);
        semP(sem);
        printf("PID %d: w trakcie ", pid);
        semInfo(sem);

        f = fopen("numer.txt", "r");
        if (f == NULL)
        {
            perror("file open error");
            exit(1);
        }
        fc = fscanf(f, "%d", &n);
        if (fc > 1)
        {
            printf("\nfc==1\n");
        }
        printf("pid: %d licznik:%d\n", pid, n);
        n++;
        
        fclose(f);
        srand(pid);
        usleep(rand()%pid*10+10000);
        f = fopen("numer.txt", "w");
        fprintf(f, "%d", n);
        fc = fscanf(f, "%d", &n);
        if (fc > 1)
        {
            printf("\nfc==1\n");
        }
        
        fclose(f);

        semV(sem);
        printf("PID %d: po ", pid);
        semInfo(sem);
        
    }
    semClose(sem);
    return 0;
}
