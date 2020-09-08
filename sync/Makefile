sync:	sync.o
	$(CC) -o sync sync.o

sync.o:	sync.c
	$(CC) -c -o sync.o sync.c

clean:
	rm -f sync sync.o

install:
	install -d -m 755 sync ${DESTDIR}/bin
