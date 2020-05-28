#include "obsluga.h"

void obsluga(char action, int signl)
{

    switch (action)
    {
    case 'd':
        if (signal(signl, SIG_DFL) == SIG_ERR)//domyslna obsluga sygnalu
        {
            perror("signal error");
            exit(1);
        }
        break;
    case 'i':
        if (signal(signl, SIG_IGN) == SIG_ERR)//ignorowanie sygnalu
        {
            perror("signal error");
            exit(1);
        }
        break;
    case 'p':

        if (signal(signl, handler) == SIG_ERR)//wlasna obsluga sygnalu
        {
            perror("signal error");
            exit(1);
        }
        break;
    default:
        break;
    }
    pause();
}
void handler(int signl)//funkcja obslugujaca sygnal
{
    printf("%d\n", signl);
}