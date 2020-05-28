#include "sem.h"
int main(int argc, char const *argv[])
{
    /*--------------sprawdzanie argumtow--------------------------*/
    if (argc != 2)
    {
        printf("zla ilosc argumentow\n");
        exit(1);
    }
    else if (((argv[1][0] != 'i') && (argv[1][0] != 'r') && (argv[1][0] != 'p') && (argv[1][0] != 'v') && (argv[1][0] != 'q')) || argv[1][1] != '\0') //sprawdaznie poprawności argumentu
    {
        printf("bledna operacja\n");
        exit(1);
    }
    /*------------------------------------------------------------*/
    semid tmp;
    switch (argv[1][0])
    {
    case 'i':
        tmp = semCreate("/semtest", 1);
        semInfo(tmp);
        semClose(tmp);
        break;
    case 'r':
        semRemove("/semtest");
        break;
    case 'p':
        tmp = semOpen("/semtest");
        semP(tmp);
        semInfo(tmp);
        semClose(tmp);
        break;
    case 'v':
        tmp = semOpen("/semtest");
        semV(tmp);
        semInfo(tmp);
        semClose(tmp);
        break;
    case 'q':
        tmp = semOpen("/semtest");
        semInfo(tmp);
        semClose(tmp);
        break;
    default:
        break;
    }
    return 0;
}
