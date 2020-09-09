all:	random

random:	random.o
	$(CC) -o random random.o

random.o:	random.c
	$(CC) -c -o random.o random.c

clean:
	rm -f random random.o

install:
	install -d -m 755 random /bin

