#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include "procinfo.h"
int childFunc(){
    procinfo("potomek");
    return 0;
}
int main(int argc, char const *argv[])
{

    for (int i = 0; i < 3; i++)
    {
        if(clone(childFunc,0,0,0)==-1){
            perror("clone error");
            exit(1);
        }
    }
    
    return 0;
}
