#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>
int compare_and_swap(int* val,int exp,int new);
#define LW 5 //liczba wątków
#define I 10 //liczba iteracji w wątku
#define END LW *I
#define MICROSLEEP 100000
int licznik = 0;
int blokada = false;
void *thread(void *arg);
pthread_mutex_t mutex;
struct thread_arg //argument dla wątku
{
    pthread_t id; //id wątku (od pthread_create)
    int num;      //numer wątku
};
int main(int argc, char const *argv[])
{
    char *check;
    pthread_mutex_init(&mutex, NULL);
    struct thread_arg thTab[LW];
    printf("\033c\n");
    for (int i = 0; i < LW; i++)
    {
        thTab[i].num = i + 1;
        if (pthread_create(&(thTab[i].id), NULL, &thread, &thTab[i]) != 0)
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
    printf("\033[0m\033[%d;%dH L=%d %s\n", LW + 1, 0, licznik, check);
    return 0;
}
void *thread(void *arg)
{
    struct thread_arg *tmp = arg;
    int l, i = 0;
    do
    {
        while (compare_and_swap(&blokada, 0, 1) != 0)
            ; // spin lock
        l = licznik;
        printf("\033[%d;%dH(%d/%d)\n", tmp->num, 12, i, licznik);//wyswietla stan licznika
        l++;
        printf("\033[33m\033[%d;%dH(%d/\033[31m%d)\033[0m\n", tmp->num, 12, i, licznik);
        usleep(MICROSLEEP);
        licznik = l;
        
        printf("\033[%d;%dH\033[K\n", tmp->num, 12);
        //sekcja krytyczna
        pthread_mutex_lock(&mutex);
        blokada = 0;
        pthread_mutex_unlock(&mutex);
        //reszta
        printf("\033[0m\033[%d;%dHpthread(%d)\033[0m\n", tmp->num, 0, tmp->num);//wyświetla nr pthread
        i++;
    } while (i < I);

    return NULL;
}
int compare_and_swap(int *val, int exp, int new)
{
    pthread_mutex_lock(&mutex);
    int tmp = *val;
    if (*val == exp)
        *val = new;
    pthread_mutex_unlock(&mutex);
    return tmp;
}
