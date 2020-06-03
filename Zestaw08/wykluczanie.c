#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define LW 5 //liczba wątków
int licznik = 0;
void *thread(void *arg);
pthread_mutex_t mutex;
struct thread_arg
{                      /* Used as argument to thread_start() */
    pthread_t id;      /* ID returned by pthread_create() */
    int num;           /* Application-defined thread # */
    char *argv_string; /* From command-line argument */
};
int main(int argc, char const *argv[])
{
pthread_mutex_init(&mutex,NULL);
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
        if(pthread_join(thTab[i].id,NULL)!=0){
            printf("pthread join error\n");
            exit(1);
        }
        
    }
    printf("\033[0m\033[%d;%dH\n",LW,0);
    return 0;
}
void *thread(void *arg)
{
    struct thread_arg *tmp=arg;
    int l;
    for(int i=0;i<10;i++)
    {
    printf("\033[0m\033[%d;%dHpthread(%d)\033[0m\n", tmp->num, 0,tmp->num);
    pthread_mutex_lock(&mutex);
    l=licznik;
    printf("\033[%d;%dH(%d/%d)\n", tmp->num, 12,l,licznik);
l++;
    printf("\033[33m\033[%d;%dH(%d/\033[31m%d)\033[0m\n", tmp->num, 12,l,licznik);
    usleep(100000);
    licznik=l;
    printf("\033[%d;%dH(%d/\033[31m%d)\033[0m\n", tmp->num, 12,l,licznik);
    pthread_mutex_unlock(&mutex);
    }
    printf("\033[32m\033[%d;%dH(%d/%d)\033[0m\n", tmp->num, 12,l,licznik);
    return NULL;
}
