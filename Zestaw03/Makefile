CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm
.PHONY: all clean tar
all: obsluga.x wysylaj.x grupa.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)

#procinfo.o:	procinfo.c procinfo.h
#'basename $(CURDIR)'
#main.o:	main.c	procinfo.h
#	gcc -o main.o main.c
obsluga.x: obsluga.o main1.o procinfo.o
grupa.x: procinfo.o obsluga.x
wysylaj.x: obsluga.x
#	$(CC) $(CFLAGS) -c -o $@ $<





#program.x: $(addsuffix .o,$(sources))

%.o: %.c
	$(CC) $(CFLAGS) $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(wildcard *.[ox])


tar: clean
	(cd ../; tar -cvzf $(archiwum).tar.gz  $(katalog) )

