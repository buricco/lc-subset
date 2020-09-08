basename:	basename.o
	$(CC) -o basename basename.o

basename.o:	basename.c
	$(CC) -c -o basename.o basename.c

clean:
	rm -f basename basename.o

install:
	install -d -m 755 basename ${DESTDIR}/bin
