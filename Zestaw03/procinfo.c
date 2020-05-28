#include "procinfo.h"
int procinfo(const char* name){
   
    uid_t uid=getuid();
    gid_t gid=getgid();
    pid_t pid=getpid();
    pid_t ppid=getppid();
    //pid_t pgrp=getpgrp();
    pid_t pgid=getpgid(pid);
    printf("UID:%d GID:%d PID:%d PPID:%d PGID:%d %s \n",uid,gid,pid,ppid,pgid,name);
    /*
    getgid();
    getpid();
    getppid();
    getpgrp();
    getpgid(pid);
   */
   return 0;
}