all:	tty

tty:	tty.o
	$(CC) -o tty tty.o

tty.o:	tty.c
	$(CC) -c -o tty.o tty.c

clean:
	rm -f tty tty.o

install:
	install -d -m 755 tty ${DESTDIR}/bin
