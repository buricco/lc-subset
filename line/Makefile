line:	line.o
	$(CC) -o line line.o

line.o:	line.c
	$(CC) -c -o line.o line.c

clean:
	rm -f line line.o

install:
	install -d -m 755 line /bin

