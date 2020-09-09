all:	dmesg

dmesg:	dmesg.o
	$(CC) -o dmesg dmesg.o

dmesg.o:	dmesg.c
	$(CC) -c -o dmesg.o dmesg.c

clean:
	rm -f dmesg dmesg.o

