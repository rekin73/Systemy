#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "obsluga.h"
#include "procinfo.h"
int main(int argc, char const *argv[])
{
    if (argc != 3)//sprawdzanie ilości argumentów
    {
        printf("bledna ilosc argumentow\n");
        return 0;
    }
    else if (((argv[1][0] != 'd') && (argv[1][0] != 'i') && (argv[1][0] != 'p')) || argv[1][1] != '\0')//sprawdaznie poprawności argumentu
    {
        printf("bledna operacja:\n");
        return 0;
    }
    
    procinfo(argv[0]);
    obsluga(argv[1][0],atoi(argv[2]));
    return 0;
}
