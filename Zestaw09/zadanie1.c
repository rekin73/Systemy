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
    printf("\033c\n");
    for (int i = 0; i < LW; i++)
    {
        thTab[i].num = i + 1;
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
    printf("\033[0m\033[%d;%dHLicznik: %d %s\n", LW + 1, 0, licznik, check);
    return 0;
}

void *thread(void *arg)
{
    struct thread_arg *tmp = arg;
    int tmpInd = tmp->num - 1;
    int l;
    for (int i = 0; i < I; i++)
    {
        wybieranie[tmpInd] = true;
        numer[tmpInd] = max() + 1;
        wybieranie[tmpInd] = false;
        //printf("\033[0m\033[%d;%dHpthread(%d) czekanie\033[0m\n", tmp->num, 0, tmp->num); // czekaj
        for (int j = 0; j < LW; j++)
        {

            while (wybieranie[j])
            {
                //printf("\033[%d;%dH\033[1K",tmp->num, 25);
                //printf("\033[%d;%dH\033[31m(%d)\033[0m\n", tmp->num, 25, licznik);//prawa strona
                // continue;S
            }
            while (numer[j] != 0 && (numer[j] < numer[tmpInd] || (numer[j] == numer[tmpInd] && j < tmpInd)))
            {
               // printf("\033[0m\033[%d;%dHpthread(%d) czekanie\033[0m\n", tmp->num, 0, tmp->num); // czekaj
                //printf("\033[%d;%dH\033[31m(%d)\033[0m\n", tmp->num, 25, licznik);//prawa strona
                // continue;
            }
        }

        l = licznik;
        l++;
         //usleep(1);
        licznik = l;

        if (i == I - 1)
            printf("\033[%d;%dH\033[32m(%d/%d)\033[0m\n", tmp->num, 25, i, licznik); //prawa strona
        else
            printf("\033[%d;%dH\033[31m(%d/%d)\033[0m\n", tmp->num, 25, i, licznik); //prawa strona
        numer[tmpInd] = 0;
        //printf("\033[%d;%dH\033[1K",tmp->num, 25);
        printf("\033[0m\033[%d;%dHpthread(%d) czekanie\033[0m\n", tmp->num, 0, tmp->num); //lewa strona
        //reszta
    }
    return NULL;
}
int max()
{
    int tmp = numer[0];
    for (int i = 1; i < LW; i++)
    {
        if (numer[i] > tmp)
            tmp = numer[i];
    }
    return tmp;
}