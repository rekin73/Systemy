CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lrt -lsem
.PHONY: all clean tar
all: libsem.a semuse.x prog.x powielacz.x a61.x czytelnik.x pisarz.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)
semuse.x: 

powielacz.x: prog.x

prog.x:

sem.o: sem.c
	$(CC) -c $<

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


tar: clean
	(cd ../; tar -cvzf $(archiwum).tar.gz  $(katalog) )

