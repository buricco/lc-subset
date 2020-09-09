all:	mkdir

mkdir:	mkdir.o setmode.o
	$(CC) -o mkdir mkdir.o setmode.o

mkdir.o:	mkdir.c
	$(CC) -c -o mkdir.o mkdir.c

setmode.o:	setmode.c
	$(CC) -c -o setmode.o setmode.c

clean:
	rm -f mkdir mkdir.o setmode.o

install:
	install -d -m 755 mkdir ${DESTDIR}/bin
