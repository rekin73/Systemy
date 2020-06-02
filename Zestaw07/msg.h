#ifndef MSG_H
#define MSG_H
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef struct
{
char msg[40];
int msg_len;
unsigned int msg_prio;
}komunikat;
 // Tworzy kolejkę komunikatów o nazwie name i zwraca do niej deskryptor.
int msgCreate(const char *name);
 // Otwiera kolejkę komunikatów o nazwie name i zwraca do niej deskryptor.
int msgOpen(const char *name);
 // Zamyka dostęp do kolejki od deskryptorze msgid.
void msgClose(int msgid);
 // Usuwa kolejkę komunikatów nazwie name.
void msgRm(const char *name);
 // Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid.
void msgSend(int msgid, komunikat *msg);
 // Odbiera z kolejki msgid komunikat i zapisuje go do msg.
void msgRecv(int msgid, komunikat *msg);
 // Wypisuje wszystkie informacje o kolejce komunikatów uzyskane przy pomocy mq_getattr();.
void msgInfo(int msgid);

 
#endif