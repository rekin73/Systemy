#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "prod.h"

void prod(int *fdes)
{
    char *buf = malloc(100);//bufor i alokacja pamięci dla niego
    if (close(fdes[0]) == -1)// zamkniencie pliku do odczytu danych
    {
        perror("close error");
        exit(1);
    }
    int f;
    if ((f = open("magazyn.txt", O_RDONLY)) == -1)//otwarcie pliku z tekstem oryginalnym
    {
        perror("open error");
        exit(1);
    }
    int rd;
    while ((rd = read(f, buf, 100)) != 0)//zczytywanie danych z pliku "f" do bufforu
    {
        if (rd == -1)
        {
            perror("read error");
            exit(1);
        }
        printf("%dprod:%s\n",rd,buf);//wymieniane dane wyswietlane są na ekranie
        if (write(fdes[1], buf, rd) == -1)//zapisanie do potoku
        {
            perror("write error");
            exit(1);
        }
        usleep(100+rand()%1000);//losowe usypianie mające symulować różne czasy wykonywania się programów
    }

    if (close(f) == -1)//zamknięci pliku "f"
    {
        perror("file close error");
        exit(1);
    }
    if (close(fdes[1]) == -1)//zamknięcie pliku zapisu
    {
        perror("close error");
        exit(1);
    }
    free(buf);
       if ((wait(NULL)) == -1) //procesy macierzyste czekają na potomne
    {
        perror("wait error");
    }
}