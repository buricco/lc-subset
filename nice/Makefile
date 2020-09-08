nice:	nice.o pwcache.o
	$(CC) -o nice nice.o pwcache.o

nice.o:	nice.c
	$(CC) -c -o nice.o nice.c

pwcache.o:	pwcache.c
	$(CC) -c -o pwcache.o pwcache.c

clean:
	rm -f nice nice.o pwcache.o

install:
	install -d -m 755 nice /usr/bin

