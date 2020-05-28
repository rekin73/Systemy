CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm
.PHONY: all clean tar
all: drzewko1.x drzewko2.x macierzysty.x potomny.x zombi.x orphan.x execute.x A1.x
sources = main procinfo
objects=$(addsuffix .o,$(sources))
autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)

#procinfo.o:	procinfo.c procinfo.h
#'basename $(CURDIR)'
#main.o:	main.c	procinfo.h
#	gcc -o main.o main.c
drzewko1.x: procinfo.o

#	$(CC) $(CFLAGS) -c -o $@ $<
drzewko2.x: procinfo.o

macierzysty.x: procinfo.o

potomny.x: procinfo.o

A1.x: procinfo.o
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

