all:	readlink

readlink:	readlink.o
	$(CC) -o readlink readlink.o

readlink.o:	readlink.c
	$(CC) -c -o readlink.o readlink.c

clean:
	rm -f readlink readlink.o

install:
	install -d -m 755 readlink /bin

