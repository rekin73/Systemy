#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    char *buf = malloc(100);

    int f, fifo;
    if ((f = open("schowek.txt", O_WRONLY | O_TRUNC)) == -1)
    {
        perror("open error");
        exit(1);
    }

    if ((fifo = open(argv[1], O_RDONLY)) == -1)
    {
        perror("open error");
        exit(1);
    }

    int rd;
    while ((rd = read(fifo, buf, 100)) != 0)
    {
        printf("kons:%s\n", buf);
        if (write(f, buf, rd) == -1)
        {
            perror("write error");
            exit(1);
        }
    }

    if (close(f) == -1)
    {
        perror("file close error");
        exit(1);
    }

    if (close(fifo) == -1)
    {
        perror("close error");
        exit(1);
    }
    free(buf);

    exit(0);
}
