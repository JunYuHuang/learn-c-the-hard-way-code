PREFIX?=/usr/local
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1
CFLAGS+=-I${PREFIX}/apr/include/apr-util-1 -D_LARGEFILE64_SOURCE=1
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: devpkg.o bstrlib.o db.o shell.o commands.o
	$(CC) -o devpkg devpkg.o bstrlib.o db.o shell.o commands.o $(LDFLAGS)

devpkg.o: devpkg.c
	$(CC) $(CFLAGS) -c devpkg.c

bstrlib.o: bstrlib.c
	$(CC) $(CFLAGS) -c bstrlib.c

db.o: db.c
	$(CC) $(CFLAGS) -c db.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

commands.o: commands.c
	$(CC) $(CFLAGS) -c commands.c

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM
