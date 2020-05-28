CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lshmem -lsem -lrt

.PHONY: all clean tar
all: libshmem.so shmuse.x producent.x konsument.x glowny.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)
producent.x:

konsument.x:

glowny.x:

shmem.o: shmem.c
	$(CC) -c -O -fPIC $<

libshmem.so: shmem.o
	$(CC) -shared -o $@ $<

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

