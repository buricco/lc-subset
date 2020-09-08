uname:	uname.o
	$(CC) -o uname uname.o

uname.o:	uname.c
	$(CC) -c -o uname.o uname.c

clean:
	rm -f uname uname.o

install:
	install -d -m 755 uname ${DESTDIR}/bin
