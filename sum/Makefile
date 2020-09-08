sum:	sum.o
	$(CC) -o sum sum.o

sum.o:	sum.c
	$(CC) -c -o sum.o sum.c

clean:
	rm -f sum sum.o

install:
	install -d -m 755 sum ${DESTDIR}/bin
