all:	logname

logname:	logname.o
	$(CC) -o logname logname.o

logname.o:	logname.c
	$(CC) -c -o logname.o logname.c

clean:
	rm -f logname logname.o

install:
	install -d -m 755 logname ${DESTDIR}/usr/bin
