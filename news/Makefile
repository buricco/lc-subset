news:	news.o pwcache.o
	$(CC) -o news news.o pwcache.o

news.o:	news.c
	$(CC) -c -o news.o news.c

pwcache.o:	pwcache.c
	$(CC) -c -o pwcache.o pwcache.c

clean:
	rm -f news news.o pwcache.o

install:
	install -d -m 755 news /usr/bin

