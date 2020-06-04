#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define LW 5   //Licba wątków
#define I 1000 //liczba iteracji w wątku
#define END LW *I
void *thread(void *arg);
void lock();
void unlock();
int max();
volatile bool wybieranie[LW];
volatile int numer[LW];
volatile int licznik = 0;
struct thread_arg //argument dla wątku
{
    pthread_t id; //id wątku (od pthread_create)
    int num;      //numer wątku
};
int main(int argc, char const *argv[])
{
    char *check;
    struct thread_arg thTab[LW];
    
    for (int i = 0; i < LW; i++)
    {
        thTab[i].num = i;
        if (pthread_create(&(thTab[i].id), NULL, &thread, &(thTab[i])) != 0)
        {
            printf("pthread create error\n");
            exit(1);
        }
    }
    for (int i = 0; i < LW; i++)
    {
        if (pthread_join(thTab[i].id, NULL) != 0)
        {
            printf("pthread join error\n");
            exit(1);
        }
    }
    if (licznik == END)
        check = "OK";
    else
        check = "ERROR";
    printf("Licznik: %d %s\n",licznik, check);
    return 0;
}

void *thread(void *arg)
{
    struct thread_arg *tmp = arg;
    int id = tmp->num;

    for (int i = 0; i < I; i++)
    {
        lock(id);
        licznik++;
        unlock(id);
    }
    return NULL;
}
/* int max()
{
    int max = numer[0];
    for (int i = 1; i < LW; i++)
    {
        if (numer[i] > max)
            max = numer[i];
    }
    return max;
} */
void lock(int id)
{
    wybieranie[id] = true;
    //numer[id] = max() + 1;
        int max = numer[0];
    for (int i = 1; i < LW; i++)
    {
        if (numer[i] > max)
            max = numer[i];
    }
    numer[id]=max+1;
    wybieranie[id] = false;
    for (int j = 0; j < LW; j++)
    {

        while (wybieranie[j])
            ;
        while (numer[j] != 0 && (numer[j] < numer[id] || (numer[j] == numer[id] && j < id)))
            ;
    }
    //usleep(1);
}
void unlock(int id)
{
    numer[id] = 0;
}