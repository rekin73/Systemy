#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "msg.h"
#include "kolejka.h"
int operation(int a, int b, char c, int *out);
void sighandler(int signum);
int flag = 0;
int main(int argc, char const *argv[])
{
    int mqIn = msgCreate(SERWER);
    komunikat komIn, komOut;
    int a = 0, b = 0, out = 0;
    pid_t pid;
    char s[40];
    char op;
    int mqOut;
    //komIn.msg[0]='a';
    if (signal(SIGINT, sighandler) == SIG_ERR)
    {
        perror("signal error");
        exit(1);
    }
    while (1)
    {
        msgRecv(mqIn, &komIn);
        if (flag == 1)
        {
            msgClose(mqIn);
            msgRm(SERWER);
            printf("end\n");
            return 0;
        }
        printf("msg: %s\n", komIn.mtext);
        sscanf(komIn.mtext, "./%d.key %d %c %d", &pid, &a, &op, &b);
        //printf("pid: %d\n",pid);
        sprintf(s, "./%d.key", pid);
        //printf("address: %s\n",s);
        mqOut = msgOpen(s);
        komOut.len = 40;
        //komOut.mtype = 0;
        if (operation(a, b, op, &out) == 1)
        {
            sprintf(komOut.mtext, "error\n");
        }
        else
            sprintf(komOut.mtext, "%d %c %d = %d\n", a, op, b, out);

        msgSend(mqOut,&komOut);
        //msgClose(mqOut);
    }
    return 0;
}
int operation(int a, int b, char c, int *out)
{
    //printf("op:%d %c %d=?\n",a,c,b);
    switch (c)
    {
    case '+':
        *out = a + b;
        break;
    case '-':
        *out = a - b;
        break;
    case '*':
        *out = a * b;
        break;
    case '/':
        if (b != 0)
            *out = a / b;
        else
            return 1;
        break;
    default:
        return 1;
        break;
    }
    return 0;
}
void sighandler(int signum)
{
    printf("koniec\n");
    flag = 1;
}