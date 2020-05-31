#ifndef BUFOR_H
#define BUFOR_H
#define ROZMIAR 10
typedef char towar;
typedef struct
{
    int size;           // Całkowity rozmiar bufora
    int beg;            // Pierwszy element do odczytu
    int end;            // Element za ostatnim zapisanym elementem
    towar buf[ROZMIAR]; // Dane, własny typ 'towar' może być równoważny np. 'int'
} bufor;
#endif