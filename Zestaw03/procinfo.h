#ifndef PROCINFO_H
#define PROCINFO_H
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int procinfo(const char* name);
#endif