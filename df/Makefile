all:	df

df:	df.o
	$(CC) -o df df.o

df.o:	df.c
	$(CC) -c -o df.o df.c

clean:
	rm -f df df.o

install:
	install -d -m 755 df ${DESTDIR}/bin
