#ifndef OBSLUGA_H
#define OBSLUGA_H
#include<unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
void obsluga(char action, int signl);
void handler(int signl);
#endif