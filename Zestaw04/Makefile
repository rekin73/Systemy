CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm
.PHONY: all clean tar
all: prodkons.x fifo.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)

#procinfo.o:	procinfo.c procinfo.h
#'basename $(CURDIR)'
#main.o:	main.c	procinfo.h
#	gcc -o main.o main.c
prodkons.x: prod.o kons.o
#	$(CC) $(CFLAGS) -c -o $@ $<
konsument.x:

producent.x:

fifo.x: producent.x konsument.x

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

