CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lshmem -lsem -lrt
LDPATH :=-Wl,-R .
.PHONY: all clean tar
all: libsem.a libshmem.so shmuse1.x shmuse2.x producent.x konsument.x glowny.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)
producent.x:

konsument.x:

glowny.x:
shmuse1.x:shmuse.o
	$(CC) -o $@ $^ $(LDFLAGS)
shmuse2.x:shmuse.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)
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
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

clean:
	$(RM) $(wildcard *.[ox])
	$(RM) *.a
	$(RM) *.so


tar: clean
	(cd ../; tar -cvzf $(archiwum).tar.gz  $(katalog) )

