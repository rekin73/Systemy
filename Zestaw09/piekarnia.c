#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define LW 5 //Licba wątków
void *thread(void *arg);
int max();
bool wybieranie[LW];
int numer[LW];
int licznik = 0;
struct thread_arg //argument dla wątku
{
    pthread_t id; //id wątku (od pthread_create)
    int num;      //numer wątku
};
int main(int argc, char const *argv[])
{
    struct thread_arg thTab[LW];
    printf("\033c\n");
    for (int i = 0; i < LW; i++)
    {
        thTab[i].num = i+1;
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
    printf("\033[0m\033[%d;%dH\n", LW, 0);
    return 0;
}

void *thread(void *arg)
{
    struct thread_arg *tmp = arg;
    int tmpInd=tmp->num - 1;
    while (licznik<10)
    {
        wybieranie[tmp->num] = true;
        numer[tmp->num] = max() + 1;
        wybieranie[tmp->num] = false;
        for (int j = 0; j < LW; j++)
        {
            while (wybieranie[j])
                printf("\033[0m\033[%d;%dHpthread(%d) wybieranie\033[0m\n", tmp->num, 0, tmp->num); // czekaj
            while (numer[j] != 0 &&(numer[j]<numer[tmpInd] || (numer[j]==numer[tmpInd] && j<tmpInd)))
                printf("\033[0m\033[%d;%dHpthread(%d) numer\033[0m\n", tmp->num, 0, tmp->num); // czekaj
        }
        //sekcja krytyczna
        printf("\033[0m\033[%d;%dHpoczatek %d L:%d\n",LW+2,0, tmp->num, licznik);
        if (licznik < 10)
            licznik++;
        printf("\033[0m\033[%d;%dHkoniec %d L:%d\n",LW+3,0, tmp->num, licznik);
        usleep(100000);
        numer[tmpInd] = 0;
        //reszta
    }
    return NULL;
}
int max()
{
    int tmp = numer[0];
    for (int i = 1; i < LW; i++)
    {
       if (numer[i]>tmp)
        tmp=numer[i];
    }
    return tmp;
}