all:	yes

yes:	yes.o
	$(CC) -o yes yes.o

yes.o:	yes.c
	$(CC) -c -o yes.o yes.c

clean:
	rm -f yes yes.o

install:
	install -d -m 755 yes ${DESTDIR}/bin
