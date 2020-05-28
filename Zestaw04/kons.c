#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "kons.h"

void kons(int *fdes)
{
    char *buf = malloc(100);
    if (close(fdes[1]) == -1)
    {
        perror("close error");
        exit(1);
    }
    int f;
    if ((f = open("schowek.txt", O_WRONLY | O_TRUNC)) == -1)
    {
        perror("open error");
        exit(1);
    }
    int rd;
    while ((rd=read(fdes[0], buf, 100)) != 0)
    {
        printf("kons:%s\n", buf);
        if (write(f, buf, rd) == -1)
        {
            perror("write error");
            exit(1);
        }
        usleep(rand()%100);
    }
    if (close(f) == -1)
    {
        perror("file close error");
        exit(1);
    }
    if (close(fdes[0]) == -1)
    {
        perror("close error");
        exit(1);
    }
    free(buf);
}
