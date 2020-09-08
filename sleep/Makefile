sleep:	sleep.o
	$(CC) -o sleep sleep.o

sleep.o:	sleep.c
	$(CC) -c -o sleep.o sleep.c

clean:
	rm -f sleep sleep.o

install:
	install -d -m 755 sleep ${DESTDIR}/bin
