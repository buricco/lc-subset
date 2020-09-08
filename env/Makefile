env:	env.o
	$(CC) -o env env.o

env.o:	env.c
	$(CC) -c -o env.o env.c

clean:
	rm -f env env.o

install:
	install -d -m 755 env ${DESTDIR}/bin
