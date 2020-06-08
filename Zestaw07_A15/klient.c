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
    char s[7];
    sprintf(s, "/%d", pid);
    int mqIn = msgCreate(s);
    int mqSrv;// = msgOpen(SERWER);
    komunikat kom,odp;
    //kom.msg=malloc(40);
    int a,b;
    char op;
    msgInfo(mqIn);
    while (fgets(kom.msg,40,stdin))//wczytywanie danych
    {
        a=0;
        b=0;
        mqSrv=msgOpen(SERWER);
        sscanf(kom.msg,"%d %c %d",&a,&op,&b);//wuciąganie zmiennych
        //printf("input: %s\n", s);
        sprintf(kom.msg, "/%d %d %c %d", pid, a,op,b);
        printf("msg: %s\n", kom.msg);
        kom.msg_len=8192;
        //kom.msg_prio=1;
        msgSend(mqSrv,&kom);
    msgClose(mqSrv);
        //kom = (komunikat){komMsg};
    msgRecv(mqIn,&odp);
    printf("odp: %s",odp.msg);
    }
    msgClose(mqIn);
    msgRm(s);
    return 0;
}
