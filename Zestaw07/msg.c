#include "msg.h"

int msgCreate(const char *name)
{
    //struct mq_attr *attr;
    int tmp = mq_open(name, O_CREAT | O_RDWR, 0777, NULL);
    if (tmp == -1)
    {
        perror("msg create error");
        exit(1);
    }
    return tmp;
}
int msgOpen(const char *name)
{
    int tmp = mq_open(name, O_RDWR);
    if (tmp == -1)
    {
    //printf("%s\n",name);
        perror("msg open error");
        exit(1);
    }
    return tmp;
}
void msgClose(int msgid)
{
    if (mq_close(msgid) == -1)
    {
        perror("msg close error");
        exit(1);
    }
}
void msgRm(const char *name)
{
    if (mq_unlink(name) == -1)
    {
        perror("msg remove error");
        exit(1);
    }
}
void msgSend(int msgid, komunikat *msg)
{
    if (mq_send(msgid, msg->msg, msg->msg_len, msg->msg_prio) == -1)
    {
        //printf("%s\n",(msg->msg));
        perror("msg send error");
        exit(1);
    }
    //printf("%s\n",(msg->msg));
}
void msgRecv(int msgid, komunikat *msg)
{
        //printf("pre: %s %d\n",(msg)->msg, (msg)->msg_len);
        int tmp=mq_receive(msgid, msg->msg, 8192, NULL);
    if (tmp == -1)
    {
        msgInfo(msgid);
        printf("%s %d\n",msg->msg, tmp);
        perror("msg recieve error");
        //printf("%d\n",errno);
        if (errno != EINTR)
            exit(1);
    }
        //printf("%s %d tmp:%d\n",(msg)->msg, (msg)->msg_len,tmp);
}
void msgInfo(int msgid)
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
}