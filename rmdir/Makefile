all:	rmdir

rmdir:	rmdir.o
	$(CC) -o rmdir rmdir.o

rmdir.o:	rmdir.c
	$(CC) -c -o rmdir.o rmdir.c

clean:
	rm -f rmdir rmdir.o

install:
	install -d -m 755 rmdir ${DESTDIR}/bin
