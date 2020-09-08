renice:	renice.o
	$(CC) -o renice renice.o

renice.o:	renice.c
	$(CC) -c -o renice.o renice.c

clean:
	rm -f renice renice.o

install:
	install -d -m 755 renice /bin

