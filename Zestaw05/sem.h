#ifndef SEM_H
#define SEM_H
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
typedef sem_t *semid;

semid semCreate(const char *name, int val);
//Tworzy semafor z wartością początkową val.

void semRemove(const char *name);
// Usuwa semafor.

semid semOpen(const char *name);
// Uzyskuje dostęp do istniejącego semafora.

void semClose(semid sem);
//Zamyka semafor w danym procesie.

void semP(semid sem);
//Opuszcza semafor: zmniejsza wartość semafora o 1 lub czeka.

void semV(semid sem);
//Podnosi semafor: zwiększa wartość semafora o 1 lub wznawia czekający proces.

void semInfo(semid sem);
//Funkcja wypisuje informację o wartości semafora, ewentualnie gdy system dopuszcza taką możliwość także o liczbie czekających procesów.

#endif