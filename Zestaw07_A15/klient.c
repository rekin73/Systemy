#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "msg.h"
#include <sys/types.h>
#include <unistd.h>
#include "kolejka.h"
int main(int argc, char const *argv[])
{
    pid_t pid = getpid();
    char s[40];
    sprintf(s, "./%d.key", pid);
    int mqIn = msgCreate(s);
    int mqSrv;// = msgOpen(SERWER);
    komunikat kom,odp;
    //kom.msg=malloc(40);
    int a,b;
    char op;
    //msgInfo(mqIn);
    while (fgets(kom.mtext,40,stdin))//wczytywanie danych
    {
        a=0;
        b=0;
        mqSrv=msgOpen(SERWER);
        sscanf(kom.mtext,"%d %c %d",&a,&op,&b);//wuciąganie zmiennych
        //printf("input: %s\n", s);
        sprintf(kom.mtext, "./%d.key %d %c %d", pid, a,op,b);
        printf("msg: %s\n", kom.mtext);
        kom.len=40;
        //kom.msg_prio=1;
        msgSend(mqSrv,&kom);
    //msgClose(mqSrv);
        //kom = (komunikat){komMsg};
    msgRecv(mqIn,&odp);
    printf("odp: %s",odp.mtext);
    }
    msgClose(mqIn);
    msgRm(s);
    return 0;
}
