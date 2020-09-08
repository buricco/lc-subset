realpath:	realpath.o
	$(CC) -o realpath realpath.o

realpath.o:	realpath.c
	$(CC) -c -o realpath.o realpath.c

clean:
	rm -f realpath realpath.o

install:
	install -d -m 755 realpath /bin

