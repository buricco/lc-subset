mount:	mount.o
	$(CC) -o mount mount.o

mount.o:	mount.c
	$(CC) -c -o mount.o mount.c

clean:
	rm -f mount mount.o

install:
	install -d -m 755 mount /bin

