all:	cat

cat:	cat.o
	$(CC) -o cat cat.o

cat.o:	cat.c
	$(CC) -c -o cat.o cat.c

clean:
	rm -f cat cat.o

install:
	install -d -m 755 cat ${DESTDIR}/bin
