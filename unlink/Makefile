unlink:	unlink.o
	$(CC) -o unlink unlink.o

unlink.o:	unlink.c
	$(CC) -c -o unlink.o unlink.c

clean:
	rm -f unlink unlink.o

install:
	install -d -m 755 unlink ${DESTDIR}/bin
