#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    switch (fork())
    {
    case -1:
         perror("fork error");
            exit(1);
        break;
    case 0:
        sleep(5);
        exit(0);
    break;
    default:
    
    exit(0);
        break;
    }
    return 0;
}