#include "sem.h"
semid semCreate(const char *name, int val)
{
    semid tmp;
    printf("tworzenie semafora o nazwie %s\n", name);
    if ((tmp = sem_open(name, O_CREAT | O_EXCL, 0666, val)) == SEM_FAILED)
    {
        perror("semaphor create error");
        exit(1);
    }
    else
    {
        printf("semafor %s utworzony pomyslnie\n", name);

    
        return tmp;
    }
}

void semRemove(const char *name)
{
    printf("usuwanie semafora %s\n", name);
    if (sem_unlink(name) == -1)
    {
        perror("semaphor remove error");
        exit(1);
    }
    else
    {
        printf("semafor %s usuniety pomyslnie\n", name);
    }
}

semid semOpen(const char *name)
{
    semid tmp;
    printf("otwieranie semafora %s\n", name);
    if ((tmp = sem_open(name, 0)) == SEM_FAILED)
    {
        perror("semaphor open error");
        exit(1);
    }
    else
    {
        printf("semafor %s otwarty pomyslnie\n", name);
        return tmp;
    }
}

void semClose(semid sem)
{
    if (sem_close(sem) == -1)
    {
        perror("semaphor close error");
        exit(1);
    }
    else
    {
        printf("semafor zamkniety pomyslnie\n");
    }
}

void semP(semid sem)
{
    printf("opuszczanie semafora\n");
    if (sem_wait(sem) == -1)
    {
        perror("sem wait error");
        exit(1);
    }
}

void semV(semid sem)
{
    printf("podnoszenie semafora\n");
    if (sem_post(sem) == -1)
    {
        perror("sem post error");
        exit(1);
    }
}

void semInfo(semid sem)
{
    int tmp;
    if (sem_getvalue(sem, &tmp) == -1)
    {
        perror("sem getvalue error");
        exit(1);
    }
    else
    {
        printf("semafor ma wartosc %d\n", tmp);
        if (tmp < 0)
        {
            printf("%d procesy oczekujace\n",-tmp);
        }
    }
}