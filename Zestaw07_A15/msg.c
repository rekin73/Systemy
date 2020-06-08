#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "msg.h"

int msgCreate(const char *name)
{
    char cmd[40];
    sprintf(cmd, "touch %s", name);
    //struct mq_attr *attr;
    if (system(cmd) == -1)
    {
        perror("system");
    }
    key_t key = ftok(name, 'A');
    int tmp;
    if (key == -1)
    {
        perror("msg create key error");
        exit(1);
    }
    tmp = msgget(key, IPC_CREAT | 0666);
    if (tmp == -1)
    {
        perror("msgget create error");
        exit(1);
    }
    return tmp;
}

int msgOpen(const char *name)
{
    //printf("%s\n", name);
    key_t key =ftok(name, 'A');
        if (key == -1)
    {
        perror("key open error");
        exit(1);
    }
    int tmp = msgget(key, 0666);
    if (tmp == -1)
    {
        perror("msg open error");
        exit(1);
    }
    return tmp;
}
void msgClose(int msgid)
{
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msg close error");
        exit(1);
    }
}
void msgRm(const char *name)
{
    char cmd[40];
    sprintf(cmd, "rm %s", name);

    if (system(cmd) == -1)
    {
        perror("system");
    }
}
void msgSend(int msgid, komunikat *msg)
{
    //printf("send:%s\n",(msg->mtext));
    if (msgsnd(msgid, msg, msg->len, 0) == -1)
    {
        //printf("%s\n",(msg->msg));
        perror("msg send error");
        exit(1);
    }
}
void msgRecv(int msgid, komunikat *msg)
{
    //printf("pre: %s %d\n",(msg)->msg, (msg)->msg_len);
    int tmp = msgrcv(msgid, msg, sizeof(msg->mtext), 0, 0);
    if (tmp == -1)
    {
        //msgInfo(msgid);
        //printf("%s %d\n",msg->msg, tmp);
        perror("msg recieve error");
        //printf("%d\n",errno);
        if (errno != EINTR)
            exit(1);
    }
    //printf("%s %d tmp:%d\n",(msg)->msg, (msg)->msg_len,tmp);
}
/* void msgInfo(int msgid)
{
    struct mq_attr attr;
    if (mq_getattr(msgid,&attr) == -1){
        perror("msg info error");
        exit(1);
    }
    printf("mq_flags   : %ld\n",attr.mq_flags);
    printf("mq_maxmsg  : %ld\n",attr.mq_maxmsg);
    printf("mq_msgsize : %ld\n",attr.mq_msgsize);
    printf("mq_curmsg  : %ld\n",attr.mq_curmsgs);
} */