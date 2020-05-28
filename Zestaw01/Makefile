CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm
.PHONY: all clean tar
all: main.x main2.x main3.x main4.x
sources = main procinfo
objects=$(addsuffix .o,$(sources))
autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)

#procinfo.o:	procinfo.c procinfo.h
#'basename $(CURDIR)'
#main.o:	main.c	procinfo.h
#	gcc -o main.o main.c
main.x:	main.o	procinfo.o

#	$(CC) $(CFLAGS) -c -o $@ $<
main2.x: main2.o kopiuj.o

main3.x: main3.o procesy.o procinfo.o

main4.x: main4.o lider.o procinfo.o
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

