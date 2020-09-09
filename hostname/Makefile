all:	hostname

hostname:	hostname.o
	$(CC) -o hostname hostname.o

hostname.o:	hostname.c
	$(CC) -c -o hostname.o hostname.c

clean:
	rm -f hostname hostname.o

install:
	install -d -m 755 hostname ${DESTDIR}/bin
	ln -s hostname ${DESTDIR}/bin/domainname
