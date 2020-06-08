CFLAGS	:= -O3 -Wall -std=c99
#CFLAGS	+= -Wall
LDFLAGS := -s -lm -pthread -L. -lmsg -lrt
LDPATH :=-Wl,-R .
.PHONY: all clean tar
all: libmsg.a libmsg.so klient.x serwer.x


autor=HubertKalinowski
katalog=`basename $(CURDIR)`
archiwum=$(autor)_$(katalog)
klient.x:


msgs.o: msg.c
	$(CC) -c $< -o $@

msgd.o: msg.c
	$(CC) -c -O -fPIC $< -o $@

libmsg.so: msgd.o
	$(CC) -shared -o $@ $<

libmsg.a: msgs.o
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
	$(RM) *.key


tar: clean
	(cd ../; tar -cvzf $(archiwum).tar.gz  $(katalog) )

