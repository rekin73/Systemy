#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include "procinfo.h"
int procinfo(const char* name){
   
    uid_t uid=getuid();
    gid_t gid=getgid();
    pid_t pid=getpid();
    pid_t ppid=getppid();
    //pid_t pgrp=getpgrp();
    pid_t pgid=getpgid(pid);
    printf("Name = %s, UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d \n",name,uid,gid,pid,ppid,pgid);
    /*
    getgid();
    getpid();
    getppid();
    getpgrp();
    getpgid(pid);
   */
   return 0;
}