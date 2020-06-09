CFLAGS	:= -Wall -std=c99 -O3
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lpthread -lrt
LDPATH :=-Wl,-R .
.PHONY: all clean tar
all: wykluczanie_tas.x wykluczanie_swap.x 


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)
wykluczanie_tas.x:

wykluczanie_swap.x:


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

