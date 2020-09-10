all:	pgrep

pgrep:	pgrep.o
	$(CC) -o pgrep pgrep.o

pgrep.o:	pgrep.c
	$(CC) -c -o pgrep.o pgrep.c

clean:
	rm -f pgrep pgrep.o

install:
	install -d -m 755 pgrep ${DESTDIR}/bin
	ln -s pgrep ${DESTDIR}/bin/pkill
