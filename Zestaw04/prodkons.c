#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "prod.h"
#include "kons.h"
int main(int argc, char const *argv[])
{
    
    int fdes[2];//deskryptor plików
    if(pipe(fdes)==-1)//utworzenie potoku
    {
        perror("pipe error");
        exit(1);
    }
    switch (fork())
    {
    case -1:
        perror("fork error");
        exit(1);
        break;
    case 0:
        kons(fdes);//funkcja "konsumenta"
        break;
    default:
    prod(fdes);//funkcja "producenta"
        break;
    }
    return 0;
}
