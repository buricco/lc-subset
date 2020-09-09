all:	uptime

uptime:	uptime.o
	$(CC) -o uptime uptime.o

uptime.o:	uptime.c
	$(CC) -c -o uptime.o uptime.c

clean:
	rm -f uptime uptime.o

install:
	install -d -m 755 uptime ${DESTDIR}/bin
