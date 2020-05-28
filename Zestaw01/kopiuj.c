#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "kopiuj.h"
#include <stdio.h>
#include <stdlib.h>
void kopiuj(char *source, char *destination)
{
    size_t bufSize = 1024;
    char *buf = malloc(bufSize);
    int src = open(source, O_RDONLY);
    if (src == -1)
    {
        perror("source file open error");
        exit(1);
    }
    int dest = open(destination, O_WRONLY | O_CREAT, 0666);
    if (dest == -1)
    {
        perror("destination file open error");
        exit(1);
    }
    //buf[bufSize-1]='\0';
    ssize_t amountRead;
    ssize_t amountWritten;
    while ((amountRead = read(src, buf, bufSize - 1)) > 0)
    {

        amountWritten = write(dest, buf, amountRead);
        if (amountWritten == -1)
        {
            perror("write file error");
            exit(1);
        }
    }
    if (amountRead == -1)
    {
        perror("read file error");
        exit(1);
    }

    close(src);
    close(dest);
    free(buf);
}