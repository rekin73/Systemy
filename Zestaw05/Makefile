CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lsem -lshmem -lrt -Wl,-R .
.PHONY: all clean tar A6
all: libsem.a libshmem.so semuse.x prog.x powielacz.x A6


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)


semuse.x: 

powielacz.x: prog.x

prog.x:

A6: a6.x czytelnik1.x pisarz1.x czytelnik2.x pisarz2.x czytelnik3.x pisarz3.x

sem.o: sem.c
	$(CC) -c $<

shmem.o: shmem.c
	$(CC) -c -O -fPIC $<

libshmem.so: shmem.o
	$(CC) -shared -o $@ $<

libsem.a: sem.o
	ar rv $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(wildcard *.[ox])
	$(RM) *.a
	$(RM) *.so


tar: clean
	(cd ../; tar -cvzf $(archiwum).tar.gz  $(katalog) )

