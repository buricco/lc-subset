all:	banner

banner:	banner.o
	$(CC) -o banner banner.o

banner.o:	banner.c
	$(CC) -c -o banner.o banner.c

clean:
	rm -f banner banner.o

