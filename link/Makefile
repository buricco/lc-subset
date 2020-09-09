all:	link

link:	link.o
	$(CC) -o link link.o

link.o:	link.c
	$(CC) -c -o link.o link.c

clean:
	rm -f link link.o

install:
	install -d -m 755 link ${DESTDIR}/bin
